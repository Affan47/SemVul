initialize()
{
	_lastframe = 0;

	_rate = new Control (Control::FloatType, "rate", "Rate", "Hz/sec");
	_rate->_floatLB = -((float) _sampleRate);
	_rate->_floatUB =  (float) _sampleRate;
	_rate->setValue (0.0f);
	_controls.push_back (_rate);

	_minfreq = new Control (Control::FloatType, "min_freq", "Min Freq", "Hz");
	_minfreq->_floatLB = 0.0;
	_minfreq->_floatUB = _sampleRate / 2;
	_minfreq->setValue (_minfreq->_floatLB);
	_controls.push_back (_minfreq);

	_maxfreq = new Control (Control::FloatType, "max_freq", "Max Freq", "Hz");
	_maxfreq->_floatLB = 0.0;
	_maxfreq->_floatUB = _sampleRate / 2;
	_maxfreq->setValue (_maxfreq->_floatUB);
	_controls.push_back (_maxfreq);


	_tmpfilt = new float[_fftN];

	_inited = true;
}
