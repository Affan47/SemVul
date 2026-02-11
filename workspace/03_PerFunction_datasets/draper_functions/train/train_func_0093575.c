vmm_Init(int show, int hide)
{
	int i;
	VMM_Mode *lastm = NULL;
	vmm_Close();


	for(i = 0; modetab[i].width; ++i)
	{
		VMM_Mode *m;
		double nominal_aspect;
		VMM_IMode *im = &modetab[i];
		if(im->flags & hide)
			continue;
		if(!(im->flags & show))
			continue;
		m = calloc(1, sizeof(VMM_Mode));
		if(!m)
			return -1;
		m->id = im->id;
		m->width = im->width;
		m->height = im->height;
		m->flags = im->flags;
		if(im->flags & VMM_3_2)
			nominal_aspect = 3.0f / 2.0f;
		else if(im->flags & VMM_5_4)
			nominal_aspect = 5.0f / 4.0f;
		else if(im->flags & VMM_16_10)
			nominal_aspect = 16.0f / 10.0f;
		else if(im->flags & VMM_16_9)
			nominal_aspect = 16.0f / 9.0f;
		else
			nominal_aspect = 4.0f / 3.0f;
		if(im->width)
			m->aspect = nominal_aspect / im->width * im->height;
		else
			m->aspect = 1.0f;
		if(im->name)
			m->name = strdup(im->name);
		if(lastm)
			lastm->next = m;
		else
			vmm_modes = m;
		lastm = m;
	}

	return 0;
}
