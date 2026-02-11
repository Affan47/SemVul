parse_rc(int *argc_ptr, char ***argv_ptr, char *name)
{
     struct stat st;
     FILE *rcfile;
     int size;
     char *buf, *p;

     if (stat(name, &st))
	  return;
     buf = malloc(st.st_size+1);
     if (!buf) {
	  error(0, 0, _("not enough memory to process rc file"));
	  return;
     }
     rcfile = fopen(name, "r");
     if (!rcfile) {
	  error(0, errno, _("cannot open `%s'"), name);
	  return;
     }
     size = fread(buf, 1, st.st_size, rcfile);
     buf[size] = 0;
     fclose(rcfile);

     for (p = strtok(buf, "\n"); p; p = strtok(NULL, "\n")) {
	  int argc;
	  char **argv;

	  argcv_get(p, "", "#", &argc, &argv);
	  expand_argcv(argc_ptr, argv_ptr, argc, argv);
	  free(argv);
     }
     free(buf);
}
