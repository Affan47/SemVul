build_v2_eh_catch_objects (void)
{
  int count=0;
  ident_data_tuple *ref;

  if (!vec_safe_length (ehtype_list))
    return;

  FOR_EACH_VEC_ELT (*ehtype_list, count, ref)
    {
      char buf[BUFSIZE];
      bool impl = is_implemented (ref->ident);
      bool excpt = objc2_objc_exception_attr (lookup_interface (ref->ident));
      snprintf (buf, BUFSIZE, "OBJC_EHTYPE_$_%s", IDENTIFIER_POINTER (ref->ident));
      if (!impl && excpt)

	ref->data = create_extern_decl (objc_v2_ehtype_template, buf);
      else

	ref->data = build_ehtype (ref->ident, buf, !excpt);
    }
}
