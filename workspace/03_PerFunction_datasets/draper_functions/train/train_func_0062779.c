get_cpu_counter (ImplVtable *vtable, MonoBoolean only_value, MonoCounterSample *sample)
{
	MonoProcessError error;
	int id = GPOINTER_TO_INT (vtable->arg);
	int pid = id >> 5;
	id &= 0x1f;
	if (!only_value) {
		fill_sample (sample);
		sample->baseValue = 1;
	}
	sample->counterType = predef_counters [predef_categories [CATEGORY_CPU].first_counter + id].type;
	switch (id) {
	case COUNTER_CPU_USER_TIME:
		sample->rawValue = mono_cpu_get_data (pid, MONO_CPU_USER_TIME, &error);
		return TRUE;
	case COUNTER_CPU_PRIV_TIME:
		sample->rawValue = mono_cpu_get_data (pid, MONO_CPU_PRIV_TIME, &error);
		return TRUE;
	case COUNTER_CPU_INTR_TIME:
		sample->rawValue = mono_cpu_get_data (pid, MONO_CPU_INTR_TIME, &error);
		return TRUE;
	case COUNTER_CPU_DCP_TIME:
		sample->rawValue = mono_cpu_get_data (pid, MONO_CPU_DCP_TIME, &error);
		return TRUE;
	case COUNTER_CPU_PROC_TIME:
		sample->rawValue = mono_cpu_get_data (pid, MONO_CPU_IDLE_TIME, &error);
		return TRUE;
	}
	return FALSE;
}
