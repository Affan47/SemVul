f0r_update(f0r_instance_t instance, double time,
                const uint32_t* inframe, uint32_t* outframe)
{
	mask0mate_instance_t* inst = (mask0mate_instance_t*)instance;

	uint32_t* dst = outframe;
	const uint32_t* src = inframe;
	const uint32_t* alpha = inst->mask_blurred;

	int len = inst->w * inst->h;

	int i;
	for ( i = 0; i < len; i++ ) {
		*dst = *src & (*alpha | 0x00ffffff);
		dst++;
		src++;
		alpha++;
	}

}
