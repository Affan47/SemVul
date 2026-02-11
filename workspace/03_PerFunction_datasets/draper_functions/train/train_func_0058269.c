file_handle_name_safe(Var handle) {
  if(!file_handle_valid(handle))
	 return NULL;
  else
	 return file_handle_name(handle);
}
