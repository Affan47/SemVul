mv88e6352_eeprom_is_readonly(struct dsa_switch *ds)
{
	int ret;

	ret = mv88e6xxx_reg_read(ds, REG_GLOBAL2, GLOBAL2_EEPROM_OP);
	if (ret < 0)
		return ret;

	if (!(ret & GLOBAL2_EEPROM_OP_WRITE_EN))
		return -EROFS;

	return 0;
}
