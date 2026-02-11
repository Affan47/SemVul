omapi_set_value (omapi_object_t *h,
			      omapi_object_t *id,
			      omapi_data_string_t *name,
			      omapi_typed_data_t *value)
{
	omapi_object_t *outer;
	isc_result_t status;

#if defined (DEBUG)
	if (!value) {
		log_info ("omapi_set_value (%.*s, NULL)",
			  (int)name -> len, name -> value);
	} else if (value -> type == omapi_datatype_int) {
		log_info ("omapi_set_value (%.*s, %ld)",
			  (int)name -> len, name -> value,
			  (long)value -> u.integer);
	} else if (value -> type == omapi_datatype_string) {
		log_info ("omapi_set_value (%.*s, %.*s)",
			  (int)name -> len, name -> value,
			  (int)value -> u.buffer.len, value -> u.buffer.value);
	} else if (value -> type == omapi_datatype_data) {
		log_info ("omapi_set_value (%.*s, %ld %lx)",
			  (int)name -> len, name -> value,
			  (long)value -> u.buffer.len,
			  (unsigned long)value -> u.buffer.value);
	} else if (value -> type == omapi_datatype_object) {
		log_info ("omapi_set_value (%.*s, %s)",
			  (int)name -> len, name -> value,
			  value -> u.object
			  ? (value -> u.object -> type
			     ? value -> u.object -> type -> name
			     : "(unknown object)")
			  : "(unknown object)");
	}
#endif

	for (outer = h; outer -> outer; outer = outer -> outer)
		;
	if (outer -> type -> set_value)
		status = (*(outer -> type -> set_value)) (outer,
							  id, name, value);
	else
		status = ISC_R_NOTFOUND;
#if defined (DEBUG)
	log_info (" ==> %s", isc_result_totext (status));
#endif
	return status;
}
