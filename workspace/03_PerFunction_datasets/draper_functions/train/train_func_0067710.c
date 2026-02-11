qam_demodulator_command(struct drxk_state *state,
				 int number_of_parameters)
{
	int status;
	u16 cmd_result;
	u16 set_param_parameters[4] = { 0, 0, 0, 0 };

	set_param_parameters[0] = state->m_constellation;
	set_param_parameters[1] = DRXK_QAM_I12_J17;

	if (number_of_parameters == 2) {
		u16 set_env_parameters[1] = { 0 };

		if (state->m_operation_mode == OM_QAM_ITU_C)
			set_env_parameters[0] = QAM_TOP_ANNEX_C;
		else
			set_env_parameters[0] = QAM_TOP_ANNEX_A;

		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_ENV,
				     1, set_env_parameters, 1, &cmd_result);
		if (status < 0)
			goto error;

		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM,
				     number_of_parameters, set_param_parameters,
				     1, &cmd_result);
	} else if (number_of_parameters == 4) {
		if (state->m_operation_mode == OM_QAM_ITU_C)
			set_param_parameters[2] = QAM_TOP_ANNEX_C;
		else
			set_param_parameters[2] = QAM_TOP_ANNEX_A;

		set_param_parameters[3] |= (QAM_MIRROR_AUTO_ON);


		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM,
				     number_of_parameters, set_param_parameters,
				     1, &cmd_result);
	} else {
		pr_warn("Unknown QAM demodulator parameter count %d\n",
			number_of_parameters);
		status = -EINVAL;
	}

error:
	if (status < 0)
		pr_warn("Warning %d on %s\n", status, __func__);
	return status;
}
