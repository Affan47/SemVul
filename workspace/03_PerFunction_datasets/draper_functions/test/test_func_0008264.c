mt312_get_inversion(struct mt312_state *state,
			       enum fe_spectral_inversion *i)
{
	int ret;
	u8 vit_mode;

	ret = mt312_readreg(state, VIT_MODE, &vit_mode);
	if (ret < 0)
		return ret;

	if (vit_mode & 0x80)
		*i = (vit_mode & 0x40) ? INVERSION_ON : INVERSION_OFF;

	return 0;
}
