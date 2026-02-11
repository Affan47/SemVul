r820t_imr_prepare(struct r820t_priv *priv)
{
	int rc;


	memcpy(priv->regs, r820t_init_array, sizeof(r820t_init_array));


	rc = r820t_write_reg_mask(priv, 0x05, 0x20, 0x20);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x07, 0, 0x10);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x0a, 0x0f, 0x0f);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x0b, 0x60, 0x6f);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x0c, 0x0b, 0x9f);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x0f, 0, 0x08);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x18, 0x10, 0x10);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x1c, 0x02, 0x02);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x1e, 0x80, 0x80);
	if (rc < 0)
		return rc;


	rc = r820t_write_reg_mask(priv, 0x06, 0x20, 0x20);

	return rc;
}
