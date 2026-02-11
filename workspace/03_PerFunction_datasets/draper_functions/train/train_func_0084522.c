ike_header_create_version(int major, int minor)
{
	ike_header_t *this = ike_header_create();

	this->set_maj_version(this, major);
	this->set_min_version(this, minor);
	if (major == IKEV2_MAJOR_VERSION)
	{
		this->set_initiator_flag(this, TRUE);
	}
	return this;
}
