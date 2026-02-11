snd_hdspm_get_sync_check(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	int val = -1;

	switch (hdspm->io_type) {
	case RayDAT:
		switch (kcontrol->private_value) {
		case 0:
			val = hdspm_wc_sync_check(hdspm); break;
		case 7:
			val = hdspm_tco_sync_check(hdspm); break;
		case 8:
			val = hdspm_sync_in_sync_check(hdspm); break;
		default:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->private_value-1);
		}
		break;

	case AIO:
		switch (kcontrol->private_value) {
		case 0:
			val = hdspm_wc_sync_check(hdspm); break;
		case 4:
			val = hdspm_tco_sync_check(hdspm); break;
		case 5:
			val = hdspm_sync_in_sync_check(hdspm); break;
		default:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->private_value-1);
		}
		break;

	case MADI:
		switch (kcontrol->private_value) {
		case 0:
			val = hdspm_wc_sync_check(hdspm); break;
		case 1:
			val = hdspm_madi_sync_check(hdspm); break;
		case 2:
			val = hdspm_tco_sync_check(hdspm); break;
		case 3:
			val = hdspm_sync_in_sync_check(hdspm); break;
		}
		break;

	case MADIface:
		val = hdspm_madi_sync_check(hdspm);
		break;

	case AES32:
		switch (kcontrol->private_value) {
		case 0:
			val = hdspm_wc_sync_check(hdspm); break;
		case 9:
			val = hdspm_tco_sync_check(hdspm); break;
		case 10 :
			val = hdspm_sync_in_sync_check(hdspm); break;
		default:
			 val = hdspm_aes_sync_check(hdspm,
					 kcontrol->private_value-1);
		}
		break;

	}

	if (hdspm->tco) {
		switch (kcontrol->private_value) {
		case 11:

			val = hdspm_tco_input_check(hdspm, HDSPM_TCO1_TCO_lock);
			break;
		case 12:

			val = hdspm_tco_input_check(hdspm,
				HDSPM_TCO1_LTC_Input_valid);
			break;
		default:
			break;
		}
	}

	if (-1 == val)
		val = 3;

	ucontrol->value.enumerated.item[0] = val;
	return 0;
}
