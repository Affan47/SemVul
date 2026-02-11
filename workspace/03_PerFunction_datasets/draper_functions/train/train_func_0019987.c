mono_cpu_get_data (int cpu_id, MonoCpuData data, MonoProcessError *error)
{
	gint64 value = 0;

	if (error)
		*error = MONO_PROCESS_ERROR_NONE;
	switch (data) {
	case MONO_CPU_USER_TIME:
		get_cpu_times (cpu_id, &value, NULL, NULL, NULL, NULL);
		break;
	case MONO_CPU_PRIV_TIME:
		get_cpu_times (cpu_id, NULL, &value, NULL, NULL, NULL);
		break;
	case MONO_CPU_INTR_TIME:
		get_cpu_times (cpu_id, NULL, NULL, &value, NULL, NULL);
		break;
	case MONO_CPU_DCP_TIME:
		get_cpu_times (cpu_id, NULL, NULL, NULL, &value, NULL);
		break;
	case MONO_CPU_IDLE_TIME:
		get_cpu_times (cpu_id, NULL, NULL, NULL, NULL, &value);
		break;

	case MONO_CPU_END:

		return 0;
	}
	return value;
}
