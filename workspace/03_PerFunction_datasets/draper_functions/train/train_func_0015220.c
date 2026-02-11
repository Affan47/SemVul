xkl_config_rec_write_to_file(XklEngine * engine,
			     const gchar * file_name,
			     const XklConfigRec * data,
			     const gboolean binary)
{
	if ((!binary
	     && !(xkl_engine_priv(engine, features) &
		  XKLF_CAN_OUTPUT_CONFIG_AS_ASCII))
	    || (binary
		&& !(xkl_engine_priv(engine, features) &
		     XKLF_CAN_OUTPUT_CONFIG_AS_BINARY))) {
		xkl_last_error_message =
		    "Function not supported at backend";
		return FALSE;
	}
	xkl_engine_ensure_vtable_inited(engine);
	return xkl_engine_vcall(engine, write_config_rec_to_file)
	    (engine, file_name, data, binary);
}
