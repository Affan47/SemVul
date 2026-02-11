i915_get_instruction_dst(uint32_t *data, int i, char *dstname, int do_mask)
{
	uint32_t a0 = data[i];
	int dst_nr = (a0 >> 14) & 0xf;
	char dstmask[8];
	const char *sat;

	if (do_mask) {
		if (((a0 >> 10) & 0xf) == 0xf) {
			dstmask[0] = 0;
		} else {
			int dstmask_index = 0;

			dstmask[dstmask_index++] = '.';
			if (a0 & (1 << 10))
				dstmask[dstmask_index++] = 'x';
			if (a0 & (1 << 11))
				dstmask[dstmask_index++] = 'y';
			if (a0 & (1 << 12))
				dstmask[dstmask_index++] = 'z';
			if (a0 & (1 << 13))
				dstmask[dstmask_index++] = 'w';
			dstmask[dstmask_index++] = 0;
		}

		if (a0 & (1 << 22))
			sat = ".sat";
		else
			sat = "";
	} else {
		dstmask[0] = 0;
		sat = "";
	}

	switch ((a0 >> 19) & 0x7) {
	case 0:
		if (dst_nr > 15)
			fprintf(out, "bad destination reg R%d\n", dst_nr);
		sprintf(dstname, "R%d%s%s", dst_nr, dstmask, sat);
		break;
	case 4:
		if (dst_nr > 0)
			fprintf(out, "bad destination reg oC%d\n", dst_nr);
		sprintf(dstname, "oC%s%s", dstmask, sat);
		break;
	case 5:
		if (dst_nr > 0)
			fprintf(out, "bad destination reg oD%d\n", dst_nr);
		sprintf(dstname, "oD%s%s", dstmask, sat);
		break;
	case 6:
		if (dst_nr > 3)
			fprintf(out, "bad destination reg U%d\n", dst_nr);
		sprintf(dstname, "U%d%s%s", dst_nr, dstmask, sat);
		break;
	default:
		sprintf(dstname, "RESERVED");
		break;
	}
}
