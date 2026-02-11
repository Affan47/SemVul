get_gn_memory_type(int memory_type)
{
	int result;

	switch (memory_type) {
	case NK6510_MEMORY_IN:
		result = GN_MT_IN;
		break;
	case NK6510_MEMORY_OU:
		result = GN_MT_OU;
		break;
	case NK6510_MEMORY_OUS:
		result = GN_MT_OUS;
		break;
	case NK6510_MEMORY_AR:
		result = GN_MT_AR;
		break;
	case NK6510_MEMORY_TE:
		result = GN_MT_TE;
		break;
	case NK6510_MEMORY_F1:
		result = GN_MT_F1;
		break;
	case NK6510_MEMORY_F2:
		result = GN_MT_F2;
		break;
	case NK6510_MEMORY_F3:
		result = GN_MT_F3;
		break;
	case NK6510_MEMORY_F4:
		result = GN_MT_F4;
		break;
	case NK6510_MEMORY_F5:
		result = GN_MT_F5;
		break;
	case NK6510_MEMORY_F6:
		result = GN_MT_F6;
		break;
	case NK6510_MEMORY_F7:
		result = GN_MT_F7;
		break;
	case NK6510_MEMORY_F8:
		result = GN_MT_F8;
		break;
	case NK6510_MEMORY_F9:
		result = GN_MT_F9;
		break;
	case NK6510_MEMORY_F10:
		result = GN_MT_F10;
		break;
	case NK6510_MEMORY_F11:
		result = GN_MT_F11;
		break;
	case NK6510_MEMORY_F12:
		result = GN_MT_F12;
		break;
	case NK6510_MEMORY_F13:
		result = GN_MT_F13;
		break;
	case NK6510_MEMORY_F14:
		result = GN_MT_F14;
		break;
	case NK6510_MEMORY_F15:
		result = GN_MT_F15;
		break;
	case NK6510_MEMORY_F16:
		result = GN_MT_F16;
		break;
	case NK6510_MEMORY_F17:
		result = GN_MT_F17;
		break;
	case NK6510_MEMORY_F18:
		result = GN_MT_F18;
		break;
	case NK6510_MEMORY_F19:
		result = GN_MT_F19;
		break;
	case NK6510_MEMORY_F20:
		result = GN_MT_F20;
		break;
	default:
		result = GN_MT_XX;
		break;
	}
	return (result);
}
