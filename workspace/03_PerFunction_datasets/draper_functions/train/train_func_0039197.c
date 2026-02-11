p7_tracealign_MSA(const ESL_MSA *premsa, P7_TRACE **tr, int M, int optflags, ESL_MSA **ret_postmsa)
{
  const ESL_ALPHABET *abc  = premsa->abc;
  ESL_MSA      *msa        = NULL;
  int          *inscount   = NULL;
  int          *matmap     = NULL;
  int          *matuse     = NULL;
  int           idx;
  int           alen;
  int           status;

  if ((status = map_new_msa(tr, premsa->nseq, M, optflags, &inscount, &matuse, &matmap, &alen)) != eslOK) return status;

  if (optflags & p7_DIGITIZE) { if ((status = make_digital_msa(NULL, premsa, tr, premsa->nseq, matuse, matmap, M, alen, optflags, &msa)) != eslOK) goto ERROR; }
  else                        { if ((status = make_text_msa   (NULL, premsa, tr, premsa->nseq, matuse, matmap, M, alen, optflags, &msa)) != eslOK) goto ERROR; }

  if ((status = annotate_rf(msa, M, matuse, matmap))                          != eslOK) goto ERROR;
  if ((status = annotate_posterior_probability(msa, tr, matmap, M, optflags)) != eslOK) goto ERROR;

  if (optflags & p7_DIGITIZE) rejustify_insertions_digital(     msa, inscount, matmap, matuse, M);
  else                        rejustify_insertions_text   (abc, msa, inscount, matmap, matuse, M);


  esl_msa_SetName     (msa, premsa->name, -1);
  esl_msa_SetDesc     (msa, premsa->desc, -1);
  esl_msa_SetAccession(msa, premsa->acc,  -1);

  for (idx = 0; idx < premsa->nseq; idx++)
    {
      esl_msa_SetSeqName       (msa, idx, premsa->sqname[idx], -1);
      if (msa->sqacc)  esl_msa_SetSeqAccession  (msa, idx, premsa->sqacc[idx], -1);
      if (msa->sqdesc) esl_msa_SetSeqDescription(msa, idx, premsa->sqdesc[idx], -1);
      msa->wgt[idx] = premsa->wgt[idx];
    }

  if (premsa->flags & eslMSA_HASWGTS)
    msa->flags |= eslMSA_HASWGTS;

  free(inscount);
  free(matmap);
  free(matuse);
  *ret_postmsa = msa;
  return eslOK;

 ERROR:
  if (msa      != NULL) esl_msa_Destroy(msa);
  if (inscount != NULL) free(inscount);
  if (matmap   != NULL) free(matmap);
  if (matuse   != NULL) free(matuse);
  *ret_postmsa = NULL;
  return status;
}
