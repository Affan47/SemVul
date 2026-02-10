libhydra_init()
{
	private_hydra_t *this;

	if (hydra)
	{
		this = (private_hydra_t*)hydra;
		ref_get(&this->ref);
		return !this->integrity_failed;
	}

	INIT(this,
		.public = {
			.attributes = attribute_manager_create(),
		},
		.ref = 1,
	);
	hydra = &this->public;

	this->public.kernel_interface = kernel_interface_create();

	if (lib->integrity &&
		!lib->integrity->check(lib->integrity, "libhydra", libhydra_init))
	{
		DBG1(DBG_LIB, "integrity check of libhydra failed");
		this->integrity_failed = TRUE;
	}
	return !this->integrity_failed;
}
