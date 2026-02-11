storeb (zword addr, zbyte value)
{

	if (addr >= h_dynamic_size)
		runtime_error (ERR_STORE_RANGE);

	if (addr == H_FLAGS + 1) {

		h_flags &= ~(SCRIPTING_FLAG | FIXED_FONT_FLAG);
		h_flags |= value & (SCRIPTING_FLAG | FIXED_FONT_FLAG);

		if (value & SCRIPTING_FLAG) {
			if (!ostream_script)
				script_open ();
		} else {
			if (ostream_script)
				script_close ();
		}


	}

	SET_BYTE (addr, value);

}
