uea_send_cmvs_e4(struct uea_softc *sc)
{
	int i, ret, len;
	void *cmvs_ptr;
	const struct firmware *cmvs_fw;
	int ver = 2;


	ret = uea_write_cmv_e4(sc, 1, E4_SA_CNTL, 0, 0, 1);
	if (ret < 0)
		return ret;


	ret = uea_read_cmv_e4(sc, 2, E4_SA_INFO, 55, 0, &sc->stats.phy.firmid);
	if (ret < 0)
		return ret;
	uea_info(INS_TO_USBDEV(sc), "ATU-R firmware version : %x\n",
			sc->stats.phy.firmid);


	ret = len = request_cmvs(sc, &cmvs_ptr, &cmvs_fw, &ver);
	if (ret < 0)
		return ret;


	if (ver == 2) {
		struct uea_cmvs_v2 *cmvs_v2 = cmvs_ptr;

		for (i = 0; i < len; i++) {
			ret = uea_write_cmv_e4(sc, 1,
				get_unaligned_le32(&cmvs_v2[i].group),
				get_unaligned_le32(&cmvs_v2[i].address),
				get_unaligned_le32(&cmvs_v2[i].offset),
				get_unaligned_le32(&cmvs_v2[i].data));
			if (ret < 0)
				goto out;
		}
	} else {

		uea_err(INS_TO_USBDEV(sc), "bad cmvs version %d\n", ver);
		goto out;
	}


	ret = uea_write_cmv_e4(sc, 1, E4_SA_CNTL, 0, 0, 2);
	uea_vdbg(INS_TO_USBDEV(sc), "Entering in R-ACT-REQ state\n");
	uea_info(INS_TO_USBDEV(sc), "modem started, waiting "
						"synchronization...\n");
out:
	release_firmware(cmvs_fw);
	return ret;
}
