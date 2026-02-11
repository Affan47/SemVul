write_page(struct mtd_info *mtd, struct nand_chip *nand,
		       const uint8_t *buf, bool use_ecc)
{
	struct docg4_priv *doc = nand->priv;
	void __iomem *docptr = doc->virtadr;
	uint8_t ecc_buf[8];

	dev_dbg(doc->dev, "%s...\n", __func__);

	writew(DOC_ECCCONF0_ECC_ENABLE |
	       DOC_ECCCONF0_UNKNOWN |
	       DOCG4_BCH_SIZE,
	       docptr + DOC_ECCCONF0);
	write_nop(docptr);


	docg4_write_buf16(mtd, buf, DOCG4_PAGE_SIZE);


	docg4_write_buf16(mtd, nand->oob_poi, 6);


	writew(nand->oob_poi[6], docptr + DOCG4_OOB_6_7);

	write_nop(docptr);
	write_nop(docptr);


	if (likely(use_ecc == true)) {

		uint8_t hamming = readb(docptr + DOC_HAMMINGPARITY);
		hamming = readb(docptr + DOC_HAMMINGPARITY);
		writew(hamming, docptr + DOCG4_OOB_6_7);
		write_nop(docptr);


		read_hw_ecc(docptr, ecc_buf);
		ecc_buf[7] = 0;
	}


	else {
		writew(nand->oob_poi[7], docptr + DOCG4_OOB_6_7);
		write_nop(docptr);
		memcpy(ecc_buf, &nand->oob_poi[8], 8);
	}

	docg4_write_buf16(mtd, ecc_buf, 8);
	write_nop(docptr);
	write_nop(docptr);
	writew(0, docptr + DOC_DATAEND);
	write_nop(docptr);

	return 0;
}
