def_tcl_set(Tcl_Interp * irp, struct userrec *u,
                struct user_entry *e, int argc, char **argv)
{
  BADARGS(4, 4, " handle type setting");

  e->type->set(u, e, argv[3]);
  return TCL_OK;
}
