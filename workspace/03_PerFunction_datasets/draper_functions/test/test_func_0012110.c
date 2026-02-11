new_qpol_terule_t(void){
		BEGIN_EXCEPTION
		{tcl_throw_error("Cannot directly create qpol_terule_t objects"); goto fail;};
		END_EXCEPTION
	fail:
		return NULL;
	}
