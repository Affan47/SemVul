efx_test_nvram(struct efx_nic *efx, struct efx_self_tests *tests)
{
	int rc = 0;

	if (efx->type->test_nvram) {
		rc = efx->type->test_nvram(efx);
		if (rc == -EPERM)
			rc = 0;
		else
			tests->nvram = rc ? -1 : 1;
	}

	return rc;
}
