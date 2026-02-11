donor_score (Genomicpos_T genomicpos, Genomicpos_T chroffset, bool revcomp, Genome_T genome, IIT_T chromosome_iit) {
  Genomicpos_T left;
  Chrnum_T chrnum;
  int nunknowns;
  char gbuffer[MAXENT_MAXLENGTH];
  UINT4 *genome_blocks;

  if (revcomp == false) {
    if ((genome_blocks = Genome_blocks(genome)) != NULL) {

      return Maxent_hr_donor_prob(genomicpos + 1U,chroffset);
    } else {
      left = genomicpos + 1 - DONOR_MODEL_LEFT_MARGIN;
      Genome_fill_buffer(&chrnum,&nunknowns,genome,left,DONOR_MODEL_LEFT_MARGIN+DONOR_MODEL_RIGHT_MARGIN+1,gbuffer,chromosome_iit);
#if 0
      printf("\n");
      printf("%s donor truestrand:+ left:%u\n",gbuffer,left);
      printf("%*s^^\n",DONOR_MODEL_LEFT_MARGIN,"");
#endif
      return Maxent_donor_prob(gbuffer);
    }

  } else {
    if ((genome_blocks = Genome_blocks(genome)) != NULL) {
      return Maxent_hr_antidonor_prob(genomicpos,chroffset);
    } else {
      left = genomicpos - DONOR_MODEL_RIGHT_MARGIN - 1;
      Genome_fill_buffer(&chrnum,&nunknowns,genome,left,DONOR_MODEL_LEFT_MARGIN+DONOR_MODEL_RIGHT_MARGIN+1,gbuffer,chromosome_iit);
      make_complement_inplace(gbuffer,DONOR_MODEL_LEFT_MARGIN+DONOR_MODEL_RIGHT_MARGIN+1);
#if 0
      printf("\n");
      printf("%s donor truestrand:- left:%u\n",gbuffer,left);
      printf("%*s^^\n",DONOR_MODEL_LEFT_MARGIN,"");
#endif
      return Maxent_donor_prob(gbuffer);
    }
  }
}
