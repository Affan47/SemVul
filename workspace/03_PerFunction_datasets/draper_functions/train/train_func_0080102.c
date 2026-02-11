hp10_dump_frame(u_int8_t *frame_ptr, int UNUSED(frame_len))
{
	struct hp10_frame *frame = (struct hp10_frame *)frame_ptr;
	unsigned int mmeindex;
	unsigned int mmecount = frame->mmecount;
	struct hp10_mmentry *mmentry;
	int i;

	frame_ptr += sizeof(struct hp10_frame);

	for (mmeindex = 0; mmeindex < mmecount; mmeindex++) {
		mmentry = (struct hp10_mmentry *)frame_ptr;
		faifa_printf(out_stream, "Frame: 0x%02hX (",
			(unsigned short int)(mmentry->mmetype));
		frame_ptr += sizeof(struct hp10_mmentry);
		if ((i = hp10_mmtype2index(mmentry->mmetype)) >= 0) {
			faifa_printf(out_stream, "%s)\n", hp10_frame_ops[i].desc);
			if (hp10_frame_ops[i].dump_frame != NULL) {
				hp10_frame_ops[i].dump_frame(mmentry->mmedata, mmentry->mmelength);
			}
		} else {
			faifa_printf(out_stream, "unknown)\n");
		}
		frame_ptr += mmentry->mmelength;
	}

	return (frame_ptr - (u_int8_t *)frame);
}
