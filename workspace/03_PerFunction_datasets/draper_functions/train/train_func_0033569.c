vector_add_point (int x, int y, rgb_t color, int intensity)
{
	point *newpoint;

	intensity *= intensity_correction;
	if (intensity > 0xff)
		intensity = 0xff;

	if (flicker && (intensity > 0))
	{
		intensity += (intensity * (0x80-(rand()&0xff)) * flicker)>>16;
		if (intensity < 0)
			intensity = 0;
		if (intensity > 0xff)
			intensity = 0xff;
	}
	newpoint = &new_list[new_index];
	newpoint->x = x;
	newpoint->y = y;
	newpoint->col = color;
	newpoint->intensity = intensity;
	newpoint->callback = 0;
	newpoint->status = VDIRTY;

	new_index++;
	if (new_index >= MAX_POINTS)
	{
		new_index--;
		logerror("*** Warning! Vector list overflow!\n");
	}
}
