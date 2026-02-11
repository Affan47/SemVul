updateUxUyUz(void)
{
	LOG;

	HklSample *sample = _samples->current;
	if(sample){
		_spinbutton_ux->set_value(hkl_parameter_get_value_unit(sample->ux));
		_spinbutton_uy->set_value(hkl_parameter_get_value_unit(sample->uy));
		_spinbutton_uz->set_value(hkl_parameter_get_value_unit(sample->uz));
		_checkbutton_Ux->set_active(sample->ux->fit);
		_checkbutton_Uy->set_active(sample->uy->fit);
		_checkbutton_Uz->set_active(sample->uz->fit);
	}
}
