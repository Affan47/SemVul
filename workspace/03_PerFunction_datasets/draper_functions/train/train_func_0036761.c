push_commandfd ARGS2((cfd,name),
FILE *cfd,
char *name)
{
  if ( (cfd==NULL) && (name==NULL) ) return;
  if ( read_depth >= NESTDEPTH-1 )
     kb_error(1354,"READs nested too deeply.\n",RECOVERABLE);

  if ( cfd == NULL )
     cfd = path_open(name,NOTDATAFILENAME);


  if( cfd==NULL && read_depth>0 && cmdfile_stack[read_depth-1].fd != stdin )
  {
    add_path_to_name(cmdfile_stack[read_depth-1].filename,name,filename);
    cfd=path_open(filename,NOTDATAFILENAME);
  }


  if ( cfd == NULL )
  { sprintf(errmsg,"Cannot open %s.",name);
    kb_error(1355,errmsg,RECOVERABLE);
  }
  if ( (cfd == stdin) && (read_depth == 1) ) read_depth = 0;

  strncpy(cmdfile_stack[read_depth].filename,name,PATHSIZE-1);
  cmdfile_stack[read_depth].datafile_flag = datafile_flag;
  if ( read_depth > 0 )
     cmdfile_stack[read_depth-1].line = line_no;
  line_no = 1;
  cmdfile_stack[read_depth].fd = commandfd = cfd;
  if ( file_no_used >= file_no_max )
  { file_names = (char**)kb_realloc((char*)file_names,
        (2*file_no_max+10)*sizeof(char*));
    file_no_max = 2*file_no_max+10;
  }
  file_names[file_no_used] = mycalloc(strlen(name)+4,1);
  strcpy(file_names[file_no_used],name);
  if ( read_depth > 0 )
  { file_no = file_no_used;
    cmdfile_stack[read_depth].file_no = file_no;
  }
  file_no_used++;
  read_depth++;
  yylex_init();
}
