SetDeviceTypeId(struct drxd_state *state)
{
	int status = 0;
	u16 deviceId = 0;

	do {
		status = Read16(state, CC_REG_JTAGID_L__A, &deviceId, 0);
		if (status < 0)
			break;

		status = Read16(state, CC_REG_JTAGID_L__A, &deviceId, 0);
		if (status < 0)
			break;
		printk(KERN_INFO "drxd: deviceId = %04x\n", deviceId);

		state->type_A = 0;
		state->PGA = 0;
		state->diversity = 0;
		if (deviceId == 0) {
			state->type_A = 1;
			printk(KERN_INFO "DRX3975D-A2\n");
		} else {
			deviceId >>= 12;
			printk(KERN_INFO "DRX397%dD-B1\n", deviceId);
			switch (deviceId) {
			case 4:
				state->diversity = 1;
			case 3:
			case 7:
				state->PGA = 1;
				break;
			case 6:
				state->diversity = 1;
			case 5:
			case 8:
				break;
			default:
				status = -1;
				break;
			}
		}
	} while (0);

	if (status < 0)
		return status;


	state->m_InitAtomicRead = DRXD_InitAtomicRead;
	state->m_InitSC = DRXD_InitSC;
	state->m_ResetECRAM = DRXD_ResetECRAM;
	if (state->type_A) {
		state->m_ResetCEFR = DRXD_ResetCEFR;
		state->m_InitFE_1 = DRXD_InitFEA2_1;
		state->m_InitFE_2 = DRXD_InitFEA2_2;
		state->m_InitCP = DRXD_InitCPA2;
		state->m_InitCE = DRXD_InitCEA2;
		state->m_InitEQ = DRXD_InitEQA2;
		state->m_InitEC = DRXD_InitECA2;
		if (load_firmware(state, DRX_FW_FILENAME_A2))
			return -EIO;
	} else {
		state->m_ResetCEFR = NULL;
		state->m_InitFE_1 = DRXD_InitFEB1_1;
		state->m_InitFE_2 = DRXD_InitFEB1_2;
		state->m_InitCP = DRXD_InitCPB1;
		state->m_InitCE = DRXD_InitCEB1;
		state->m_InitEQ = DRXD_InitEQB1;
		state->m_InitEC = DRXD_InitECB1;
		if (load_firmware(state, DRX_FW_FILENAME_B1))
			return -EIO;
	}
	if (state->diversity) {
		state->m_InitDiversityFront = DRXD_InitDiversityFront;
		state->m_InitDiversityEnd = DRXD_InitDiversityEnd;
		state->m_DisableDiversity = DRXD_DisableDiversity;
		state->m_StartDiversityFront = DRXD_StartDiversityFront;
		state->m_StartDiversityEnd = DRXD_StartDiversityEnd;
		state->m_DiversityDelay8MHZ = DRXD_DiversityDelay8MHZ;
		state->m_DiversityDelay6MHZ = DRXD_DiversityDelay6MHZ;
	} else {
		state->m_InitDiversityFront = NULL;
		state->m_InitDiversityEnd = NULL;
		state->m_DisableDiversity = NULL;
		state->m_StartDiversityFront = NULL;
		state->m_StartDiversityEnd = NULL;
		state->m_DiversityDelay8MHZ = NULL;
		state->m_DiversityDelay6MHZ = NULL;
	}

	return status;
}
