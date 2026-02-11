sst_hsw_module_load(struct sst_hsw *hsw,
	u32 module_id, u32 instance_id, char *name)
{
	int ret = 0;
	const struct firmware *fw = NULL;
	struct sst_fw *hsw_sst_fw;
	struct sst_module *module;
	struct device *dev = hsw->dev;
	struct sst_dsp *dsp = hsw->dsp;

	dev_dbg(dev, "sst_hsw_module_load id=%d, name='%s'", module_id, name);

	module = sst_module_get_from_id(dsp, module_id);
	if (module == NULL) {

		if (module_id == SST_HSW_MODULE_BASE_FW) {

			fw = dsp->pdata->fw;
			if (!fw) {
				dev_err(dev, "request Base fw failed\n");
				return -ENODEV;
			}
		} else {


			ret = request_firmware(&fw, name, dev);
			if (ret) {
				dev_info(dev, "fw image %s not available(%d)\n",
						name, ret);
				return ret;
			}
		}
		hsw_sst_fw = sst_fw_new(dsp, fw, hsw);
		if (hsw_sst_fw  == NULL) {
			dev_err(dev, "error: failed to load firmware\n");
			ret = -ENOMEM;
			goto out;
		}
		module = sst_module_get_from_id(dsp, module_id);
		if (module == NULL) {
			dev_err(dev, "error: no module %d in firmware %s\n",
					module_id, name);
		}
	} else
		dev_info(dev, "module %d (%s) already loaded\n",
				module_id, name);
out:

	if (fw && module_id != SST_HSW_MODULE_BASE_FW)
		release_firmware(fw);

	return ret;
}
