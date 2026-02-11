hkl_sample_reflection_update(HklSampleReflection *self)
{
	HklVector ki;
	HklQuaternion q;

	if(!self)
		return;


	hkl_source_compute_ki(&self->geometry->source, &ki);
	self->_hkl = ki;
	hkl_vector_rotated_quaternion(&self->_hkl, &self->geometry->holders[self->detector.idx].q);
	hkl_vector_minus_vector(&self->_hkl, &ki);

	q = self->geometry->holders[0].q;
	hkl_quaternion_conjugate(&q);
	hkl_vector_rotated_quaternion(&self->_hkl, &q);
}
