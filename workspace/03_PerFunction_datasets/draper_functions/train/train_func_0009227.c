class_signal_handler(omapi_object_t *h,
		     const char *name, va_list ap)
{
	struct class *class = (struct class *)h;
	isc_result_t status;
	int updatep = 0;
	int issubclass;

	issubclass = (h -> type == dhcp_type_subclass);

	if (!strcmp (name, "updated")) {

		if (!issubclass) {
			if (class -> name == 0 || strlen(class -> name) == 0) {
				return DHCP_R_INVALIDARG;
			}
		} else {
			if (class -> superclass == 0) {
				return DHCP_R_INVALIDARG;
			}

			if (class -> hash_string.data == NULL) {
				return DHCP_R_INVALIDARG;
			}
		}


		if (issubclass) {
			if (!class -> superclass -> hash)
				class_new_hash(&class->superclass->hash,
					       SCLASS_HASH_SIZE, MDL);

			add_hash (class -> superclass -> hash,
				  class -> hash_string.data,
				  class -> hash_string.len,
				  (void *)class, MDL);
		}


#ifdef DEBUG_OMAPI
		if (issubclass) {
			log_debug ("OMAPI added subclass %s",
				   class -> superclass -> name);
		} else {
			log_debug ("OMAPI added class %s", class -> name);
		}
#endif

		status = enter_class (class, 1, 1);
		if (status != ISC_R_SUCCESS)
			return status;
		updatep = 1;
	}


	if (h -> inner && h -> inner -> type -> signal_handler) {
		status = ((*(h -> inner -> type -> signal_handler))
			  (h -> inner, name, ap));
		if (status == ISC_R_SUCCESS)
			return status;
	}

	if (updatep)
		return ISC_R_SUCCESS;

	return ISC_R_NOTFOUND;
}
