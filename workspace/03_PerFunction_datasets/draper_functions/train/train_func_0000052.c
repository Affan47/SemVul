tcl_modules STDVAR
{
  int i;
  char *p, s[24], s2[24];
  EGG_CONST char *list[100], *list2[2];
  dependancy *dep;
  module_entry *current;

  BADARGS(1, 1, "");

  for (current = module_list; current; current = current->next) {
    list[0] = current->name;
    egg_snprintf(s, sizeof s, "%d.%d", current->major, current->minor);
    list[1] = s;
    i = 2;
    for (dep = dependancy_list; dep && (i < 100); dep = dep->next) {
      if (dep->needing == current) {
        list2[0] = dep->needed->name;
        egg_snprintf(s2, sizeof s2, "%d.%d", dep->major, dep->minor);
        list2[1] = s2;
        list[i] = Tcl_Merge(2, list2);
        i++;
      }
    }
    p = Tcl_Merge(i, list);
    Tcl_AppendElement(irp, p);
    Tcl_Free((char *) p);
    while (i > 2) {
      i--;
      Tcl_Free((char *) list[i]);
    }
  }
  return TCL_OK;
}
