ar9300_eeprom_restore_internal(struct ath_hw *ah,
					  u8 *mptr, int mdata_size)
{
#define MDEFAULT 15
#define MSTATE 100
	int cptr;
	u8 *word;
	int code;
	int reference, length, major, minor;
	int osize;
	int it;
	u16 checksum, mchecksum;
	eeprom_read_op read;

	if (ath9k_hw_use_flash(ah))
		return ar9300_eeprom_restore_flash(ah, mptr, mdata_size);

	word = zalloc(2048);
	if (!word)
		return -1;

	memcpy(mptr, &ar9300_default, mdata_size);

	read = ar9300_read_eeprom;
	if (AR_SREV_9485(ah))
		cptr = AR9300_BASE_ADDR_4K;
	else
		cptr = AR9300_BASE_ADDR;
	DBG2("ath9k: "
		"Trying EEPROM access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	cptr = AR9300_BASE_ADDR_512;
	DBG2("ath9k: "
		"Trying EEPROM access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	read = ar9300_read_otp;
	cptr = AR9300_BASE_ADDR;
	DBG2("ath9k: "
		"Trying OTP access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	cptr = AR9300_BASE_ADDR_512;
	DBG2("ath9k: "
		"Trying OTP access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	goto fail;

found:
	DBG2("ath9k: Found valid EEPROM data\n");

	for (it = 0; it < MSTATE; it++) {
		if (!read(ah, cptr, word, COMP_HDR_LEN))
			goto fail;

		if (!ar9300_check_header(word))
			break;

		ar9300_comp_hdr_unpack(word, &code, &reference,
				       &length, &major, &minor);
		DBG2("ath9k: "
			"Found block at %x: code=%d ref=%d length=%d major=%d minor=%d\n",
			cptr, code, reference, length, major, minor);
		if ((!AR_SREV_9485(ah) && length >= 1024) ||
		    (AR_SREV_9485(ah) && length > EEPROM_DATA_LEN_9485)) {
			DBG2("ath9k: "
				"Skipping bad header\n");
			cptr -= COMP_HDR_LEN;
			continue;
		}

		osize = length;
		read(ah, cptr, word, COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
		checksum = ar9300_comp_cksum(&word[COMP_HDR_LEN], length);
		mchecksum = word[COMP_HDR_LEN + osize] |
		    (word[COMP_HDR_LEN + osize + 1] << 8);
		DBG2("ath9k: "
			"checksum %x %x\n", checksum, mchecksum);
		if (checksum == mchecksum) {
			ar9300_compress_decision(ah, it, code, reference, mptr,
						 word, length, mdata_size);
		} else {
			DBG2("ath9k: "
				"skipping block with bad checksum\n");
		}
		cptr -= (COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
	}

	free(word);
	return cptr;

fail:
	free(word);
	return -1;
}
