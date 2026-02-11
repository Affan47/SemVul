zLoadMultiDNAFromMultiFasta(zVec *multi_dna, char* filename, char* snp_filename){
	if(snp_filename != NULL){
		zDie("Sequence variation cannot be handled for multifasta files yet");
	}
	return zInitMultiSequenceSpecialized(filename, multi_dna, zInitGenericDNA, sizeof(zDNA),
					zInitDNASequence, zReadDNASequence, zCreateDNASeqBlock,
					BLOCK_SIZE, BLOCK_COUNT);
}
