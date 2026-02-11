fimc_pipeline_s_power(struct fimc_pipeline *p, bool on)
{
	static const u8 seq[2][IDX_MAX - 1] = {
		{ IDX_IS_ISP, IDX_SENSOR, IDX_CSIS, IDX_FLITE },
		{ IDX_CSIS, IDX_FLITE, IDX_SENSOR, IDX_IS_ISP },
	};
	int i, ret = 0;

	if (p->subdevs[IDX_SENSOR] == NULL)
		return -ENXIO;

	for (i = 0; i < IDX_MAX - 1; i++) {
		unsigned int idx = seq[on][i];

		ret = __subdev_set_power(p->subdevs[idx], on);


		if (ret < 0 && ret != -ENXIO)
			goto error;
	}
	return 0;
error:
	for (; i >= 0; i--) {
		unsigned int idx = seq[on][i];
		__subdev_set_power(p->subdevs[idx], !on);
	}
	return ret;
}
