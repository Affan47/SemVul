r820t_compre_step(struct r820t_priv *priv,
			     struct r820t_sect_type iq[3], u8 reg)
{
	int rc;
	struct r820t_sect_type tmp;


	tmp.phase_y = iq[0].phase_y;
	tmp.gain_x  = iq[0].gain_x;

	while (((tmp.gain_x & 0x1f) < IMR_TRIAL) &&
	      ((tmp.phase_y & 0x1f) < IMR_TRIAL)) {
		if (reg == 0x08)
			tmp.gain_x++;
		else
			tmp.phase_y++;

		rc = r820t_write_reg(priv, 0x08, tmp.gain_x);
		if (rc < 0)
			return rc;

		rc = r820t_write_reg(priv, 0x09, tmp.phase_y);
		if (rc < 0)
			return rc;

		rc = r820t_multi_read(priv);
		if (rc < 0)
			return rc;
		tmp.value = rc;

		if (tmp.value <= iq[0].value) {
			iq[0].gain_x  = tmp.gain_x;
			iq[0].phase_y = tmp.phase_y;
			iq[0].value   = tmp.value;
		} else {
			return 0;
		}

	}

	return 0;
}
