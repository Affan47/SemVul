test_unit_ready(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);

	if (!check_card_ready(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;
	}

	if (!(CHK_BIT(chip->lun_mc, lun))) {
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		return TRANSPORT_FAILED;
	}

#ifdef SUPPORT_SD_LOCK
	if (get_lun_card(chip, SCSI_LUN(srb)) == SD_CARD) {
		struct sd_info *sd_card = &(chip->sd_card);

		if (sd_card->sd_lock_notify) {
			sd_card->sd_lock_notify = 0;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
			return TRANSPORT_FAILED;
		} else if (sd_card->sd_lock_status & SD_LOCKED) {
			set_sense_type(chip, lun,
				SENSE_TYPE_MEDIA_READ_FORBIDDEN);
			return TRANSPORT_FAILED;
		}
	}
#endif

	return TRANSPORT_GOOD;
}
