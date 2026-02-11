WriteRelocations(elf2fx2_cnvstruct_t* cs)
{

	memset(cs->loaddata, 0, cs->fxe2hdr.loadsize);


	word_t* loaddata = (word_t*) cs->loaddata;
	rlentry_t* reloc = cs->relocs;
	while(reloc != NULL)
	{
		rlentry_t* next = reloc->next;
		loaddata[reloc->addr >> 2] = 1;
		free(reloc);
		reloc = next;
	}


	word_t nwords = cs->fxe2hdr.loadsize >> 2;
	word_t i, rs, rp;
	for(i = 0; i < nwords; cs->fxe2hdr.nrelocs ++)
	{
		fxe2_reloc_t reloc;
		rs = 0;
		rp = 0;
		while((i < nwords) && !loaddata[i]) i ++, rs ++;
		while((i < nwords) && loaddata[i]) i ++, rp ++;


		for(reloc.skip = 0xFFFF, reloc.patch = 0; rs > 0xFFFF; rs -= 0xFFFF)
			safe_call(WriteData(cs->outf, &reloc, sizeof(fxe2_reloc_t)));


		for(reloc.skip = eswap_hword(rs), reloc.patch = 0xFFFF; rp > 0xFFFF; rp -= 0xFFFF)
		{
			safe_call(WriteData(cs->outf, &reloc, sizeof(fxe2_reloc_t)));
			rs = reloc.skip = 0;
		}


		if (rs || rp)
		{
			reloc.skip = eswap_hword(rs);
			reloc.patch = eswap_hword(rp);
			safe_call(WriteData(cs->outf, &reloc, sizeof(fxe2_reloc_t)));
		}
	}

	return 0;
}
