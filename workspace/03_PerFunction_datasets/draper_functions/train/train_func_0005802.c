read(SWFStream& in)
{
	in.ensureBytes(1);


    int flags = in.read_u8();
	stopPlayback = flags & (1 << 5);
	noMultiple   = flags & (1 << 4);
	hasEnvelope  = flags & (1 << 3);
	hasLoops     = flags & (1 << 2);
	hasOutPoint = flags & (1 << 1);
	hasInPoint  = flags & (1 << 0);

    in.ensureBytes(hasInPoint * 4 + hasOutPoint * 4 + hasLoops * 2);

	if (hasInPoint) {
		inPoint = in.read_u32();
	}

	if (hasOutPoint) {
		outPoint = in.read_u32();
	}

	if (hasLoops) {
		loopCount = in.read_u16();
	}

	if (hasEnvelope) {
		in.ensureBytes(1);
		int nPoints = in.read_u8();
		envelopes.resize(nPoints);
		in.ensureBytes(8 * nPoints);
		for (int i=0; i < nPoints; i++)
		{
			envelopes[i].m_mark44 = in.read_u32();
			envelopes[i].m_level0 = in.read_u16();
			envelopes[i].m_level1 = in.read_u16();
		}
	}
	else {
		envelopes.clear();
	}

	IF_VERBOSE_PARSE(
        log_parse("	hasEnvelope = %d", hasEnvelope);
        log_parse("	hasLoops = %d", hasLoops);
        log_parse("	hasOutPoint = %d", hasOutPoint);
        log_parse("	hasInPoint = %d", hasInPoint);
        log_parse("	inPoint = %d", inPoint);
        log_parse("	outPoint = %d", outPoint);
        log_parse("	loopCount = %d", loopCount);
        log_parse("	envelope size = %d", envelopes.size());
	);
}
