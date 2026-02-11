siena_test_chip(struct efx_nic *efx, struct efx_self_tests *tests)
{
	enum reset_type reset_method = RESET_TYPE_ALL;
	int rc, rc2;

	efx_reset_down(efx, reset_method);


	rc = efx_mcdi_reset(efx, reset_method);
	if (rc)
		goto out;

	tests->registers =
		efx_farch_test_registers(efx, siena_register_tests,
					 ARRAY_SIZE(siena_register_tests))
		? -1 : 1;

	rc = efx_mcdi_reset(efx, reset_method);
out:
	rc2 = efx_reset_up(efx, reset_method, rc == 0);
	return rc ? rc : rc2;
}
