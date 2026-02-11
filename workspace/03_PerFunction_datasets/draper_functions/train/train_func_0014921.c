reader_equals_src(
	struct rc_reader reader,
	unsigned int src_type,
	void * src)
{
	if (reader.Inst->Type != src_type) {
		return 0;
	}
	if (src_type == RC_INSTRUCTION_NORMAL) {
		return reader.U.I.Src == src;
	} else {
		return reader.U.P.Src == src;
	}
}
