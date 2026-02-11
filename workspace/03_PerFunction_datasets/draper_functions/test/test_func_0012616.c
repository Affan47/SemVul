shared_object_dlopen(s48_call_t call, s48_ref_t name, s48_ref_t complete_name_p)
{
  void *handle;
  s48_ref_t res;
  char *full_name;

  if (!s48_false_p_2(call, complete_name_p))
    {
      size_t len = strlen(s48_extract_byte_vector_readonly_2(call, name));
      full_name = s48_make_local_buf(call, len + 4);
      memcpy(full_name,
	     s48_extract_byte_vector_readonly_2(call, name),
	     len);
      memcpy(full_name + len,
	     ".so",
	     4);
    }
  else
    full_name = s48_extract_byte_vector_readonly_2(call, name);

  handle = dlopen(full_name, DLOPEN_MODE);
  if (handle == NULL)
    s48_error_2(call, "shared_object_dlopen", (char *)dlerror(), 1,
		s48_enter_byte_string_2(call, full_name));

  res = s48_make_value_2(call, void *);
  s48_unsafe_extract_value_2(call, res, void *) = handle;

  return res;
}
