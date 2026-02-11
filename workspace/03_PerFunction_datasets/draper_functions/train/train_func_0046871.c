mpt_register(MPT_CALLBACK cbfunc, MPT_DRIVER_CLASS dclass, char *func_name)
{
	u8 cb_idx;
	last_drv_idx = MPT_MAX_PROTOCOL_DRIVERS;


	for (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) {
		if (MptCallbacks[cb_idx] == NULL) {
			MptCallbacks[cb_idx] = cbfunc;
			MptDriverClass[cb_idx] = dclass;
			MptEvHandlers[cb_idx] = NULL;
			last_drv_idx = cb_idx;
			strlcpy(MptCallbacksName[cb_idx], func_name,
				MPT_MAX_CALLBACKNAME_LEN+1);
			break;
		}
	}

	return last_drv_idx;
}
