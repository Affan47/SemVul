op_w_osc(int argc, struct eel_data_t *argv)
{
	int target, wf, mm;
	wf = enum_awaveform;
	mm = enum_amixmode;
	switch(eel_get_args("ie[e]", &target, &wf, &mm))
	{
	  case 2:
		mm = WCA_ADD;
	  case 3:
		break;
	  default:
		return -1;
	}
	DBG(log_printf(D2LOG, "w_osc %d, %d, %d;\n", target, wf, mm);)
	wca_osc(target, wf, mm);
	return 1;
}
