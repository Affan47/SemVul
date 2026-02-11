process (fft_data *data, unsigned int fftn)
{
	if (!_inited || _filter->getBypassed()) {
		return;
	}

	float *filter = _filter->getValues();
	float min = _filter->getMin();
	float max = _filter->getMax();
	float filt;

	int fftN2 = (fftn+1) >> 1;

	memset(_tmpdata, 0, fftn * sizeof(fft_data));

	for (int i = 1; i < fftN2-1; i++)
	{
		filt = FTutils::f_clamp(filter[i], min, max);


 		_tmpdata[(int)filt] +=  data[i];
		if (i > 0 && filt > 0) {
			_tmpdata[fftn-((int)filt)] +=  data[fftn - i];
		}

	}

	memcpy (data, _tmpdata, fftn * sizeof(fft_data));
}
