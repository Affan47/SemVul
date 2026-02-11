gettextStubCompat_bindtextdomain(
	value v_domainname,
	value v_dirname)
{
  CAMLparam2(v_domainname, v_dirname);
  CAMLreturn(
      return_string_option (
        bindtextdomain(
          String_val(v_domainname),
          String_val(v_dirname))));
}
