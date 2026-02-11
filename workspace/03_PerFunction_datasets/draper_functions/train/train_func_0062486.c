ti_bandgap_set_sensor_data(struct ti_bandgap *bgp, int id, void *data)
{
	int ret = ti_bandgap_validate(bgp, id);
	if (ret)
		return ret;

	bgp->regval[id].data = data;

	return 0;
}
