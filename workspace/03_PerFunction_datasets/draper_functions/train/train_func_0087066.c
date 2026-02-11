snd_dice_transaction_set_enable(struct snd_dice *dice)
{
	__be32 value;
	int err = 0;

	if (dice->global_enabled)
		goto end;

	value = cpu_to_be32(1);
	err = snd_fw_transaction(dice->unit, TCODE_WRITE_QUADLET_REQUEST,
				 get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
					     GLOBAL_ENABLE),
				 &value, 4,
				 FW_FIXED_GENERATION | dice->owner_generation);
	if (err < 0)
		goto end;

	dice->global_enabled = true;
end:
	return err;
}
