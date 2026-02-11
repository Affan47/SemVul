kgd2kfd_init(unsigned interface_version, const struct kgd2kfd_calls **g2f)
{


	if (interface_version != KFD_INTERFACE_VERSION)
		return false;

	*g2f = &kgd2kfd;

	return true;
}
