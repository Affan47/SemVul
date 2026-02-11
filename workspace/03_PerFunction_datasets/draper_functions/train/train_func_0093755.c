telemetry_plt_get_trace_verbosity(enum telemetry_unit telem_unit,
					     u32 *verbosity)
{
	u32 temp = 0;
	int ret;

	if (verbosity == NULL)
		return -EINVAL;

	mutex_lock(&(telm_conf->telem_trace_lock));
	switch (telem_unit) {
	case TELEM_PSS:
		ret = intel_punit_ipc_command(
				IPC_PUNIT_BIOS_READ_TELE_TRACE_CTRL,
				0, 0, NULL, &temp);
		if (ret) {
			pr_err("PSS TRACE_CTRL Read Failed\n");
			goto out;
		}

		break;

	case TELEM_IOSS:
		ret = intel_pmc_ipc_command(PMC_IPC_PMC_TELEMTRY,
				IOSS_TELEM_TRACE_CTL_READ, NULL, 0, &temp,
				IOSS_TELEM_READ_WORD);
		if (ret) {
			pr_err("IOSS TRACE_CTL Read Failed\n");
			goto out;
		}

		break;

	default:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		ret = -EINVAL;
		break;
	}
	TELEM_EXTRACT_VERBOSITY(temp, *verbosity);

out:
	mutex_unlock(&(telm_conf->telem_trace_lock));
	return ret;
}
