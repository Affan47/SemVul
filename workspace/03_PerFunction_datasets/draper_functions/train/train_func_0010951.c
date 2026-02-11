isp1760_udc_find_ep(struct isp1760_udc *udc,
					      u16 index)
{
	unsigned int i;

	if (index == 0)
		return &udc->ep[0];

	for (i = 1; i < ARRAY_SIZE(udc->ep); ++i) {
		if (udc->ep[i].addr == index)
			return udc->ep[i].desc ? &udc->ep[i] : NULL;
	}

	return NULL;
}
