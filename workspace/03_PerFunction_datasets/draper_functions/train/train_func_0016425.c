avrftdi_transmit(PROGRAMMER * pgm, unsigned char mode, const unsigned char *buf,
			    unsigned char *data, int buf_size)
{
	avrftdi_t* pdata = to_pdata(pgm);
	if (pdata->use_bitbanging)
		return avrftdi_transmit_bb(pgm, mode, buf, data, buf_size);
	else
		return avrftdi_transmit_mpsse(pdata, mode, buf, data, buf_size);
}
