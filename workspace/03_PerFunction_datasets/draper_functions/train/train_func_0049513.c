mailimap_namespace_response_extension_free(struct mailimap_namespace_response_extension * ext)
{
  clistiter * cur;

  for(cur = clist_begin(ext->ns_values) ; cur != NULL ; cur = clist_next(cur)) {
    char * value;

    value = clist_content(cur);
    mailimap_string_free(value);
  }
  clist_free(ext->ns_values);
  mailimap_string_free(ext->ns_name);
  free(ext);
}
