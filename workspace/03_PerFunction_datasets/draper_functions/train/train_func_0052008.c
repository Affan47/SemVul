gate_handle_gcse2 (void)
{
  return (optimize > 0 && flag_gcse_after_reload
	  && optimize_function_for_speed_p (cfun));
}
