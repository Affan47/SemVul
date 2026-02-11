g84_therm_new(struct nvkm_device *device, int index, struct nvkm_therm **ptherm)
{
	struct nvkm_therm *therm;
	int ret;

	ret = nvkm_therm_new_(&g84_therm, device, index, &therm);
	*ptherm = therm;
	if (ret)
		return ret;


	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_SHUTDOWN,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_FANBOOST,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_CRITICAL,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_DOWNCLOCK,
						     NVKM_THERM_THRS_LOWER);
	return 0;
}
