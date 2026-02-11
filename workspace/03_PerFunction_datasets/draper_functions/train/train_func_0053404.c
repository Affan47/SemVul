find_matching_signature(void *mc, unsigned int csig, int cpf)
{
	struct microcode_header_intel *mc_hdr = mc;
	struct extended_sigtable *ext_hdr;
	struct extended_signature *ext_sig;
	int i;

	if (cpu_signatures_match(csig, cpf, mc_hdr->sig, mc_hdr->pf))
		return 1;


	if (get_totalsize(mc_hdr) <= get_datasize(mc_hdr) + MC_HEADER_SIZE)
		return 0;

	ext_hdr = mc + get_datasize(mc_hdr) + MC_HEADER_SIZE;
	ext_sig = (void *)ext_hdr + EXT_HEADER_SIZE;

	for (i = 0; i < ext_hdr->count; i++) {
		if (cpu_signatures_match(csig, cpf, ext_sig->sig, ext_sig->pf))
			return 1;
		ext_sig++;
	}
	return 0;
}
