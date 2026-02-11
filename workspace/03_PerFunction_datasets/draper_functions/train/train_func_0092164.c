updateSource(void)
{
	LOG;

	if(_geometry){
		double lambda = hkl_source_get_wavelength(&_geometry->source);
		_spinbutton_lambda->set_value(lambda);
	}
}
