match_mismatch_after_travfunc(bool forward,
                                          Traversealignmentstate *state,
                                          bool proteineop,
                                          unsigned long eoplength)
{
  if (proteineop) {
    if (state->processing_intron_with_1_base_left) {

      gt_assert(eoplength == 1);
      state->processing_intron_with_1_base_left = false;
      if (forward) {
        state->genomicptr   += eoplength * GT_CODON_LENGTH - 1;
        state->referenceptr += eoplength;
      }
      else {
        state->genomicptr   -= eoplength * GT_CODON_LENGTH - 1;
        state->referenceptr -= eoplength;
      }
    }
    else if (state->processing_intron_with_2_bases_left) {

      gt_assert(eoplength == 1);
      state->processing_intron_with_2_bases_left = false;
      if (forward) {
        state->genomicptr   += eoplength * GT_CODON_LENGTH - 2;
        state->referenceptr += eoplength - 1;
      }
      else {
        state->genomicptr   -= eoplength * GT_CODON_LENGTH - 2;
        state->referenceptr -= eoplength - 1;
      }
    }
    else {
      if (forward) {
        state->genomicptr   += eoplength * GT_CODON_LENGTH;
        state->referenceptr += eoplength;
      }
      else {
        state->genomicptr   -= eoplength * GT_CODON_LENGTH;
        state->referenceptr -= eoplength;
      }
    }
  }
  else {
    if (forward) {
      state->genomicptr   += eoplength;
      state->referenceptr += eoplength;
    }
    else {
      state->genomicptr   -= eoplength;
      state->referenceptr -= eoplength;
    }
  }
}
