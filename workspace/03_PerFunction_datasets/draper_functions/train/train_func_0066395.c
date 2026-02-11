brcmf_chip_cm3_set_active(struct brcmf_chip_priv *chip)
{
	struct brcmf_core *core;

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_INTERNAL_MEM);
	if (!brcmf_chip_iscoreup(core)) {
		brcmf_err("SOCRAM core is down after reset?\n");
		return false;
	}

	chip->ops->activate(chip->ctx, &chip->pub, 0);

	core = brcmf_chip_get_core(&chip->pub, BCMA_CORE_ARM_CM3);
	brcmf_chip_resetcore(core, 0, 0, 0);

	return true;
}
