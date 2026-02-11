evalnewintronifpossible(bool proteineop, bool *newexon,
                                    bool *newintron, bool lastintron,
                                    bool introncutout, bool gs2out,
                                    GthSplicedSeq *spliced_seq,
                                    Exoninfo *exon, Introninfo *intron,
                                    GthFlt *singleexonweight,
                                    GthFlt *maxsingleexonweight,
                                    GthFlt *overallexonweight,
                                    GthFlt *maxoverallexonweight,
                                    unsigned long
                                    *cumulativelengthofscoredexons,
                                    GthSA *sa,
                                    Traversealignmentstate *travstate,
                                    GtAlphabet *gen_alphabet,
                                    GthDPParam *dp_param,
                                    GthDPOptionsEST *dp_options_est,
                                    const unsigned char *gen_seq_tran,
                                    const unsigned char *ref_seq_tran,
                                    unsigned long gen_dp_start,
                                    unsigned long scoreminexonlen)
{
  unsigned long genomicexonlength, splicedpos;

  if (*newintron) {
    exon->rightgenomicexonborder = gen_dp_start + travstate->genomicptr - 1;
    exon->rightreferenceexonborder = gt_safe_cast2ulong(travstate
                                                        ->referenceptr - 1);
    *newintron = false;
    *newexon   = true;
    if (*maxsingleexonweight > 0.0) {
      exon->exonscore = (GthDbl) ((*singleexonweight) /
                                            (*maxsingleexonweight));
    }
    else
      exon->exonscore = 0.0;


    genomicexonlength = exon->rightgenomicexonborder -
                        exon->leftgenomicexonborder + 1;


    if (genomicexonlength >= scoreminexonlen) {
      *overallexonweight             += *singleexonweight;
      *maxoverallexonweight          += *maxsingleexonweight;
    }

    if (gs2out) {
      if (genomicexonlength >= scoreminexonlen)
        *cumulativelengthofscoredexons += genomicexonlength;
    }
    else
      *cumulativelengthofscoredexons += genomicexonlength;


    gt_assert(exon->leftgenomicexonborder <= exon->rightgenomicexonborder);
    gth_sa_add_exon(sa, exon);


    *singleexonweight    = (GthFlt) 0.0;
    *maxsingleexonweight = (GthFlt) 0.0;


    if (!lastintron) {

      if (introncutout) {
        splicedpos =
          gth_spliced_seq_orig_to_spliced_pos(spliced_seq,
                      gt_safe_cast2ulong(travstate->genomicptr + gen_dp_start));
        if (splicedpos == GT_UNDEF_ULONG) {


          intron->donorsiteprobability = 0.0;
        }
        else {
          intron->donorsiteprobability = (GthFlt)
                                 exp((double) dp_param->log_Pdonor[splicedpos]);
        }
      }
      else {
        intron->donorsiteprobability = (GthFlt)
                      exp((double) dp_param->log_Pdonor[travstate->genomicptr]);
      }


      if (proteineop)
        intron->donorsitescore = UNDEFINED_SPLICE_SITE_SCORE;
      else {
        gthcalcsplicesitescore(&intron->donorsitescore, travstate, gen_seq_tran,
                               ref_seq_tran, gen_alphabet, dp_options_est,
                               false);
      }
    }
  }
}
