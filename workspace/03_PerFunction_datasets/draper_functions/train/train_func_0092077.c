ntx_tags(char *id)
{
  if(!id) {
    char *name;
    n_dir dir = ntx_dopen(TAGS_DIR);

    if(!dir) die("Unable to read directory %s.", TAGS_DIR);
    while((name = ntx_dread(dir))) if(name[0] != '.') puts(name);

    ntx_dclose(dir);
  } else {
    char file[FILE_MAX];
    char *buf, *cur;
    char *state = NULL;

    seprintf(file, FILE_MAX, REFS_DIR"/%.2s", id);
    if(!(buf = ntx_find(file, id)))
      die("Unable to locate note %s in %s.", id, file);

    for(cur = strrtok(buf + SUMMARY_OFFSET, &state, FIELD_SEP);
        cur != NULL;
        cur = strrtok(NULL, &state, FIELD_SEP))
      puts(cur);

    release(buf);
  }
}
