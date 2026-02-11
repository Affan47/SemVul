writes_pair(struct rc_instruction * fullinst, rc_read_write_mask_fn cb, void * userdata)
{
	struct rc_pair_instruction * inst = &fullinst->U.P;

	if (inst->RGB.WriteMask)
		cb(userdata, fullinst, RC_FILE_TEMPORARY, inst->RGB.DestIndex, inst->RGB.WriteMask);

	if (inst->Alpha.WriteMask)
		cb(userdata, fullinst, RC_FILE_TEMPORARY, inst->Alpha.DestIndex, RC_MASK_W);

	if (inst->WriteALUResult)
		cb(userdata, fullinst, RC_FILE_SPECIAL, RC_SPECIAL_ALU_RESULT, RC_MASK_X);
}
