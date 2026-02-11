make_xatom (Display *dpy, Atom atom)
{
  char *atom_name;
  X_CALL(atom_name = XGetAtomName (dpy, atom));
  if (atom_name == NULL) return NIL;
  else {
    object kwd = intern_keyword(asciz_to_string(atom_name,GLO(misc_encoding)));
    X_CALL(XFree(atom_name));
    return kwd;
  }
}
