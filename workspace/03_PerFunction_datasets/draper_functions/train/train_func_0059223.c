_write_config_to_remote(lc_callback cb, void *cb_arg, uint32_t cb_stage)
{
	int err = 0;

	if (!cb_arg) {
		cb_arg = (void *)true;
	}

	if (is_z_remote() || is_mh_remote()) {
		if ((err = rmt->UpdateConfig(of->GetDataSize(), of->GetData(),
				cb, cb_arg, cb_stage, of->GetXmlSize(),
				of->GetXml())))
			return LC_ERROR_WRITE;
	} else {
		if ((err = rmt->WriteFlash(ri.arch->config_base,
				of->GetDataSize(), of->GetData(), ri.protocol,
				cb, cb_arg, cb_stage)))
			return LC_ERROR_WRITE;
	}

	return 0;
}
