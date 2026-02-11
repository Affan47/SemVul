get_genomic_nt (Genomicpos_T genomicpos, Genomicpos_T genomicstart,
		int genomiclength, bool watsonp) {
  char c2;

  if (watsonp) {
    return Genome_get_char_blocks(genomicstart + genomicpos);

  } else {
    c2 = Genome_get_char_blocks(genomicstart + (genomiclength - 1) - genomicpos);
    return complCode[(int) c2];
  }
}
