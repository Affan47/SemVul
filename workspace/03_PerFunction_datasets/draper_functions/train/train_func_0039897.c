nv40_sensor_style(struct nvkm_therm *therm)
{
	switch (therm->subdev.device->chipset) {
	case 0x43:
	case 0x44:
	case 0x4a:
	case 0x47:
		return OLD_STYLE;
	case 0x46:
	case 0x49:
	case 0x4b:
	case 0x4e:
	case 0x4c:
	case 0x67:
	case 0x68:
	case 0x63:
		return NEW_STYLE;
	default:
		return INVALID_STYLE;
	}
}
