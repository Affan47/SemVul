call_wrapper (ostream& out, JPL_MethodCall *jpl, unsigned depth) {
#endif
  out << "__call_";
  mangle (out, TransformInfo::of (*jpl)->assoc_obj ());
#ifdef ACMODEL
  if (jpl->get_lid () >= 0)
    out << "_" << jpl->get_lid ();
#else
  if (jpl->lid () >= 0)
    out << "_" << jpl->lid ();
#endif
  out << "_" << depth;
}
