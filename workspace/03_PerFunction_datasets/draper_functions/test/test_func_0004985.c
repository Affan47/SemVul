EnableAndResetMB(struct drxd_state *state)
{
	if (state->type_A) {

		Write16(state, EC_OC_REG_OC_MON_SIO__A, 0x0000, 0x0000);
	}


	Write16(state, HI_COMM_MB__A, 0x0000, DRX_I2C_BROADCAST);
	Write16(state, HI_COMM_MB__A, 0x0000, 0x0000);
	return 0;
}
