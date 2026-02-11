MakePMPICall(char *name) {
  int i;


  fprintf (wrapperFile, "\trc = P%s( ", name);
  for (i = 1; i <= argCounter && args[i].type.type != ELLIPSIS; i++) {
    char aname[256];
    if ((args[i].type.t_pointers == 0) && (args[i].type.array[0] == 0)) {
      sprintf(aname, "(%s)", args[i].name);
    }
    else {
      sprintf(aname, "(%s)", args[i].name);
    }
    if (i == 1) {
      fprintf (wrapperFile, " %s", aname);
    }
    else {
      fprintf (wrapperFile, ",\n%s", aname);
    }
  }
  fprintf (wrapperFile, ");\n");
}
