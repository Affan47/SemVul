lt_extension_truncate(lt_extension_t  *extension)
{
	int i;
	lt_bool_t retval = FALSE;

	lt_return_val_if_fail (extension != NULL, FALSE);

	for (i = LT_MAX_EXT_MODULES - 1; i >= 0; i--) {
		if (extension->extensions[i]) {
			lt_mem_delete_ref(&extension->parent, extension->extensions[i]);
			extension->extensions[i] = NULL;
			retval = TRUE;
			break;
		}
	}

	return retval;
}
