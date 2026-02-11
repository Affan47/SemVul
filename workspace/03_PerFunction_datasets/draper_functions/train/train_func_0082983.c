gameboard_write(char *basename, Gameboard *g){
  char *name;
  FILE *f;

  name=alloca(strlen(boarddir)+strlen(basename)+1);
  name[0]=0;
  strcat(name,boarddir);
  strcat(name,basename);

  f = fopen(name,"wb");
  if(f==NULL){
    fprintf(stderr,_("ERROR:  Could not save board state for \"%s\":\n\t%s\n"),
	    get_level_desc(),strerror(errno));
    return errno;
  }

  graph_write(&g->g,f);

  if(g->hide_lines)
    fprintf(f,"hide_lines 1\n");
  if(g->show_intersections)
    fprintf(f,"show_intersections 1\n");

  fclose(f);

  return 0;
}
