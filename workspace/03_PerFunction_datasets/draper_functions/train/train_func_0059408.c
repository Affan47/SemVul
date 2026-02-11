GetSeqC( const gnSeqI offset ) const
{
	STACK_TRACE_START
		char block;
		gnSeqI readLen = 1;
		gnSeqI real_offset = offset - 1;
		boolean success = spec->SeqRead( real_offset, &block, readLen, ALL_CONTIGS);


		list<const gnBaseFilter*>::const_iterator iter = filter_list.begin();
		for(; iter != filter_list.end(); iter++)
			block = (*iter)->Filter(block);

		if( success )
			return block;

		return GNSEQC_NULL;
	STACK_TRACE_END
}
