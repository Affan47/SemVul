stv090x_car_width(u32 srate, enum stv090x_rolloff rolloff)
{
	u32 ro;

	switch (rolloff) {
	case STV090x_RO_20:
		ro = 20;
		break;
	case STV090x_RO_25:
		ro = 25;
		break;
	case STV090x_RO_35:
	default:
		ro = 35;
		break;
	}

	return srate + (srate * ro) / 100;
}
