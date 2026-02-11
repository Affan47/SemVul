alc255_set_default_jack_type(struct hda_codec *codec)
{

	static struct coef_fw alc255fw[] = {
		WRITE_COEF(0x1b, 0x880b),
		WRITE_COEF(0x45, 0xd089),
		WRITE_COEF(0x1b, 0x080b),
		WRITE_COEF(0x46, 0x0004),
		WRITE_COEF(0x1b, 0x0c0b),
		{}
	};
	static struct coef_fw alc256fw[] = {
		WRITE_COEF(0x1b, 0x884b),
		WRITE_COEF(0x45, 0xd089),
		WRITE_COEF(0x1b, 0x084b),
		WRITE_COEF(0x46, 0x0004),
		WRITE_COEF(0x1b, 0x0c4b),
		{}
	};
	switch (codec->core.vendor_id) {
	case 0x10ec0255:
		alc_process_coef_fw(codec, alc255fw);
		break;
	case 0x10ec0236:
	case 0x10ec0256:
		alc_process_coef_fw(codec, alc256fw);
		break;
	}
	msleep(30);
}
