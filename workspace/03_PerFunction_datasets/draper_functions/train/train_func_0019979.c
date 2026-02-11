tpm_do_selftest(struct tpm_chip *chip)
{
	int rc;
	unsigned int loops;
	unsigned int delay_msec = 100;
	unsigned long duration;
	struct tpm_cmd_t cmd;

	duration = tpm_calc_ordinal_duration(chip, TPM_ORD_CONTINUE_SELFTEST);

	loops = jiffies_to_msecs(duration) / delay_msec;

	rc = tpm_continue_selftest(chip);


	if (rc)
		return rc;

	do {

		cmd.header.in = pcrread_header;
		cmd.params.pcrread_in.pcr_idx = cpu_to_be32(0);
		rc = tpm_transmit(chip, (u8 *) &cmd, READ_PCR_RESULT_SIZE, 0);


		if (rc == -ETIME) {
			dev_info(
			    &chip->dev, HW_ERR
			    "TPM command timed out during continue self test");
			msleep(delay_msec);
			continue;
		}

		if (rc < TPM_HEADER_SIZE)
			return -EFAULT;

		rc = be32_to_cpu(cmd.header.out.return_code);
		if (rc == TPM_ERR_DISABLED || rc == TPM_ERR_DEACTIVATED) {
			dev_info(&chip->dev,
				 "TPM is disabled/deactivated (0x%X)\n", rc);


			return 0;
		}
		if (rc != TPM_WARN_DOING_SELFTEST)
			return rc;
		msleep(delay_msec);
	} while (--loops > 0);

	return rc;
}
