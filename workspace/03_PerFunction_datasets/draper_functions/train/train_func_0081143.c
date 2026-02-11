hdsp_check_for_firmware (struct hdsp *hdsp, int load_on_demand)
{
	if (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		return 0;
	if ((hdsp_read (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) {
		hdsp->state &= ~HDSP_FirmwareLoaded;
		if (! load_on_demand)
			return -EIO;
		dev_err(hdsp->card->dev, "firmware not present.\n");

		if (! (hdsp->state & HDSP_FirmwareCached)) {
			if (! hdsp_request_fw_loader(hdsp))
				return 0;
			dev_err(hdsp->card->dev,
				   "No firmware loaded nor cached, please upload firmware.\n");
			return -EIO;
		}
		if (snd_hdsp_load_firmware_from_cache(hdsp) != 0) {
			dev_err(hdsp->card->dev,
				   "Firmware loading from cache failed, please upload manually.\n");
			return -EIO;
		}
	}
	return 0;
}
