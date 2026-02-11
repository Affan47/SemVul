jffs2_flash_cleanup(struct jffs2_sb_info *c) {

	if (jffs2_cleanmarker_oob(c)) {
		jffs2_nand_flash_cleanup(c);
	}


	if (jffs2_dataflash(c)) {
		jffs2_dataflash_cleanup(c);
	}


	if (jffs2_nor_wbuf_flash(c)) {
		jffs2_nor_wbuf_flash_cleanup(c);
	}


	if (jffs2_ubivol(c)) {
		jffs2_ubivol_cleanup(c);
	}
}
