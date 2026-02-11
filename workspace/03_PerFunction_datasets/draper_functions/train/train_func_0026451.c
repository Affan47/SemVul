rc_pair_foreach_source_that_rgb_reads(
	struct rc_pair_instruction * pair,
	void * data,
	rc_pair_foreach_src_fn cb)
{
	unsigned int i;
	const struct rc_opcode_info * info =
				rc_get_opcode_info(pair->RGB.Opcode);
	for(i = 0; i < info->NumSrcRegs; i++) {
		unsigned int chan;
		unsigned int swz = RC_SWIZZLE_UNUSED;


		for(chan = 0; chan < 4; chan++) {
			swz = GET_SWZ(pair->RGB.Arg[i].Swizzle, chan);
			if(swz == RC_SWIZZLE_X || swz == RC_SWIZZLE_Y
			|| swz == RC_SWIZZLE_Z || swz == RC_SWIZZLE_W)
				continue;
		}
		pair_foreach_source_callback(pair, data, cb,
					swz,
					pair->RGB.Arg[i].Source);
	}
}
