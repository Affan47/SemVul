cc_read_router(String name, String &next_name, int &next_number,
	       const char *filename, bool file_is_expr, ErrorHandler *errh)
{
  if (name && next_name)
    errh->warning("router name specified twice ('%s' and '%s')",
		  next_name.c_str(), name.c_str());
  else if (name)
    next_name = name;

  RouterT *r = read_router(filename, file_is_expr, errh);

  if (r) {
    r->flatten(errh);
    if (next_name) {
      int span = strspn(next_name.c_str(), "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_/@0123456789");
      if (span != next_name.length() || strstr(next_name.c_str(), "//") != 0
	  || next_name[0] == '/' || next_name.back() == '/')
	errh->error("router name '%s' is not a legal Click identifier", next_name.c_str());
      router_names.push_back(next_name);
    } else
      router_names.push_back(String(next_number));
    routers.push_back(r);
  }

  next_name = String();
  next_number++;
}
