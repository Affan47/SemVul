prompt_for_user_comment(Blob *pComment, Blob *pPrompt){
  const char *zEditor;
  char *zCmd;
  char *zFile;
  Blob reply, line;
  char *zComment;
  int i;

  zEditor = db_get("editor", 0);
  if( zEditor==0 ){
    zEditor = fossil_getenv("VISUAL");
  }
  if( zEditor==0 ){
    zEditor = fossil_getenv("EDITOR");
  }
#if defined(_WIN32) || defined(__CYGWIN__)
  if( zEditor==0 ){
    zEditor = mprintf("%s\\notepad.exe", fossil_getenv("SYSTEMROOT"));
#if defined(__CYGWIN__)
    zEditor = fossil_utf8_to_filename(zEditor);
    blob_add_cr(pPrompt);
#endif
  }
#endif
  if( zEditor==0 ){
    blob_append(pPrompt,
       "#\n"
       "# Since no default text editor is set using EDITOR or VISUAL\n"
       "# environment variables or the \"fossil set editor\" command,\n"
       "# and because no comment was specified using the \"-m\" or \"-M\"\n"
       "# command-line options, you will need to enter the comment below.\n"
       "# Type \".\" on a line by itself when you are done:\n", -1);
    zFile = mprintf("-");
  }else{
    zFile = db_text(0, "SELECT '%qci-comment-' || hex(randomblob(6)) || '.txt'",
                    g.zLocalRoot);
  }
#if defined(_WIN32)
  blob_add_cr(pPrompt);
#endif
  blob_write_to_file(pPrompt, zFile);
  if( zEditor ){
    zCmd = mprintf("%s \"%s\"", zEditor, zFile);
    fossil_print("%s\n", zCmd);
    if( fossil_system(zCmd) ){
      fossil_fatal("editor aborted: \"%s\"", zCmd);
    }

    blob_read_from_file(&reply, zFile);
  }else{
    char zIn[300];
    blob_zero(&reply);
    while( fgets(zIn, sizeof(zIn), stdin)!=0 ){
      if( zIn[0]=='.' && (zIn[1]==0 || zIn[1]=='\r' || zIn[1]=='\n') ){
        break;
      }
      blob_append(&reply, zIn, -1);
    }
  }
  blob_to_utf8_no_bom(&reply, 1);
  blob_to_lf_only(&reply);
  file_delete(zFile);
  free(zFile);
  blob_zero(pComment);
  while( blob_line(&reply, &line) ){
    int i, n;
    char *z;
    n = blob_size(&line);
    z = blob_buffer(&line);
    for(i=0; i<n && fossil_isspace(z[i]);  i++){}
    if( i<n && z[i]=='#' ) continue;
    if( i<n || blob_size(pComment)>0 ){
      blob_appendf(pComment, "%b", &line);
    }
  }
  blob_reset(&reply);
  zComment = blob_str(pComment);
  i = strlen(zComment);
  while( i>0 && fossil_isspace(zComment[i-1]) ){ i--; }
  blob_resize(pComment, i);
}
