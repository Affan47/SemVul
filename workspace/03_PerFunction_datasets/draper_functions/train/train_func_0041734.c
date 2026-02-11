store_accession (Table_T accsegmentpos_table, Tableint_T chrlength_table,
		 char *accession, char *chr_string, Genomicpos_T chrpos1,
		 Genomicpos_T chrpos2, bool revcompp, Genomicpos_T seglength,
		 int contigtype, unsigned int universal_coord) {
  Chrom_T chrom;
  Segmentpos_T segmentpos;

  chrom = Chrom_from_string(chr_string,mitochondrial_string,universal_coord);

  segmentpos = Segmentpos_new(chrom,chrpos1,chrpos2,revcompp,seglength,contigtype);
  Table_put(accsegmentpos_table,(void *) accession,(void *) segmentpos);


  if (chrpos2 > chrpos1 + seglength) {
    chrlength_update(chrlength_table,chrom,chrpos2);
  } else {
    chrlength_update(chrlength_table,chrom,chrpos1+seglength);
  }

  return;
}
