crypt_backend_init(struct crypt_device *ctx)
{
	if (crypto_backend_initialised)
		return 0;

	if (!gcry_control (GCRYCTL_INITIALIZATION_FINISHED_P)) {
		if (!gcry_check_version (GCRYPT_REQ_VERSION)) {
			return -ENOSYS;
		}


#if 0
		gcry_control (GCRYCTL_DISABLE_SECMEM);
		crypto_backend_secmem = 0;
#else

		gcry_control (GCRYCTL_SUSPEND_SECMEM_WARN);
		gcry_control (GCRYCTL_INIT_SECMEM, 16384, 0);
		gcry_control (GCRYCTL_RESUME_SECMEM_WARN);
#endif
		gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
	}

	snprintf(version, 64, "gcrypt %s%s",
		 gcry_check_version(NULL),
		 crypto_backend_secmem ? "" : ", secmem disabled");
	crypto_backend_initialised = 1;
	return 0;
}
