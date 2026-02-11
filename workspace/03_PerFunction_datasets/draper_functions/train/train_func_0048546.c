addHeader(const uint32 contigI, gnBaseHeader* header, const uint32 headerI){
	STACK_TRACE_START
		if(contigI == ALL_CONTIGS)
			spec->AddHeader(header, headerI);
		else{
			spec->GetSpec(contigI)->AddHeader(header, headerI);
		}
	STACK_TRACE_END
}
