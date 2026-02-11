uea_load_page_e4(struct work_struct *work)
{
	struct uea_softc *sc = container_of(work, struct uea_softc, task);
	u8 pageno = sc->pageno;
	int i;
	struct block_info_e4 bi;
	struct l1_code *p;

	uea_dbg(INS_TO_USBDEV(sc), "sending DSP page %u\n", pageno);


	if (pageno == 0) {
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = NULL;
	}

	if (sc->dsp_firm == NULL && request_dsp(sc) < 0)
		return;

	p = (struct l1_code *) sc->dsp_firm->data;
	if (pageno >= le16_to_cpu(p->page_header[0].PageNumber)) {
		uea_err(INS_TO_USBDEV(sc), "invalid DSP "
						"page %u requested\n", pageno);
		return;
	}

	if (pageno != 0) {
		__uea_load_page_e4(sc, pageno, 0);
		return;
	}

	uea_dbg(INS_TO_USBDEV(sc),
	       "sending Main DSP page %u\n", p->page_header[0].PageNumber);

	for (i = 0; i < le16_to_cpu(p->page_header[0].PageNumber); i++) {
		if (E4_IS_BOOT_PAGE(p->page_header[i].PageSize))
			__uea_load_page_e4(sc, i, 1);
	}

	uea_dbg(INS_TO_USBDEV(sc) , "sending start bi\n");

	bi.wHdr = cpu_to_be16(UEA_BIHDR);
	bi.bBootPage = 0;
	bi.bPageNumber = 0xff;
	bi.wReserved = cpu_to_be16(UEA_RESERVED);
	bi.dwSize = cpu_to_be32(E4_PAGE_BYTES(p->page_header[0].PageSize));
	bi.dwAddress = cpu_to_be32(le32_to_cpu(p->page_header[0].PageAddress));


	if (uea_idma_write(sc, &bi, E4_BLOCK_INFO_SIZE))
		uea_err(INS_TO_USBDEV(sc), "sending DSP start bi failed\n");
}
