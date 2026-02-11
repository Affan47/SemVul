radeon_delete_i2c_busses(struct radeonfb_info *rinfo)
{
	if (rinfo->i2c[0].rinfo)
		i2c_del_adapter(&rinfo->i2c[0].adapter);
	rinfo->i2c[0].rinfo = NULL;

	if (rinfo->i2c[1].rinfo)
		i2c_del_adapter(&rinfo->i2c[1].adapter);
	rinfo->i2c[1].rinfo = NULL;

	if (rinfo->i2c[2].rinfo)
		i2c_del_adapter(&rinfo->i2c[2].adapter);
	rinfo->i2c[2].rinfo = NULL;

	if (rinfo->i2c[3].rinfo)
		i2c_del_adapter(&rinfo->i2c[3].adapter);
	rinfo->i2c[3].rinfo = NULL;
}
