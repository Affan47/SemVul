InitCE(struct drxd_state *state)
{
	int status;
	enum app_env AppEnv = state->app_env_default;

	do {
		status = WriteTable(state, state->m_InitCE);
		if (status < 0)
			break;

		if (state->operation_mode == OM_DVBT_Diversity_Front ||
		    state->operation_mode == OM_DVBT_Diversity_End) {
			AppEnv = state->app_env_diversity;
		}
		if (AppEnv == APPENV_STATIC) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0000, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_PORTABLE) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0001, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_MOBILE && state->type_A) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0002, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_MOBILE && !state->type_A) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0006, 0);
			if (status < 0)
				break;
		}


		status = Write16(state, B_CE_REG_COMM_EXEC__A, 0x0001, 0);
		if (status < 0)
			break;
	} while (0);
	return status;
}
