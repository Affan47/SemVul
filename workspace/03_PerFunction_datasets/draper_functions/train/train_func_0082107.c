nvkm_therm_update(struct nvkm_therm *therm, int mode)
{
	struct nvkm_subdev *subdev = &therm->subdev;
	struct nvkm_timer *tmr = subdev->device->timer;
	unsigned long flags;
	bool immd = true;
	bool poll = true;
	int duty = -1;

	spin_lock_irqsave(&therm->lock, flags);
	if (mode < 0)
		mode = therm->mode;
	therm->mode = mode;

	switch (mode) {
	case NVKM_THERM_CTRL_MANUAL:
		nvkm_timer_alarm_cancel(tmr, &therm->alarm);
		duty = nvkm_therm_fan_get(therm);
		if (duty < 0)
			duty = 100;
		poll = false;
		break;
	case NVKM_THERM_CTRL_AUTO:
		switch(therm->fan->bios.fan_mode) {
		case NVBIOS_THERM_FAN_TRIP:
			duty = nvkm_therm_update_trip(therm);
			break;
		case NVBIOS_THERM_FAN_LINEAR:
			duty = nvkm_therm_update_linear(therm);
			break;
		case NVBIOS_THERM_FAN_OTHER:
			if (therm->cstate)
				duty = therm->cstate;
			poll = false;
			break;
		}
		immd = false;
		break;
	case NVKM_THERM_CTRL_NONE:
	default:
		nvkm_timer_alarm_cancel(tmr, &therm->alarm);
		poll = false;
	}

	if (poll)
		nvkm_timer_alarm(tmr, 1000000000ULL, &therm->alarm);
	spin_unlock_irqrestore(&therm->lock, flags);

	if (duty >= 0) {
		nvkm_debug(subdev, "FAN target request: %d%%\n", duty);
		nvkm_therm_fan_set(therm, immd, duty);
	}
}
