nvkm_therm_sensor_fini(struct nvkm_therm *therm, bool suspend)
{
	struct nvkm_timer *tmr = therm->subdev.device->timer;
	if (suspend)
		nvkm_timer_alarm_cancel(tmr, &therm->sensor.therm_poll_alarm);
	return 0;
}
