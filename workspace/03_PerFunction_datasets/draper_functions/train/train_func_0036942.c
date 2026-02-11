p7_alidisplay_Compare(const P7_ALIDISPLAY *ad1, const P7_ALIDISPLAY *ad2)
{
  if (ad1->mem && ad2->mem)
    {
      if (ad1->memsize != ad2->memsize)                  return eslFAIL;
      if (memcmp(ad1->mem, ad2->mem, ad1->memsize) != 0) return eslFAIL;
    }

  if (esl_strcmp(ad1->rfline,  ad2->rfline)  != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->mmline,  ad2->mmline)  != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->csline,  ad2->csline)  != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->model,   ad2->model)   != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->mline,   ad2->mline)   != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->aseq,    ad2->aseq)    != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->ppline,  ad2->ppline)  != eslOK) return eslFAIL;
  if (ad1->N != ad2->N)                                return eslFAIL;

  if (esl_strcmp(ad1->hmmname, ad2->hmmname) != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->hmmacc,  ad2->hmmacc)  != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->hmmdesc, ad2->hmmdesc) != eslOK) return eslFAIL;
  if (ad1->hmmfrom != ad2->hmmfrom)                    return eslFAIL;
  if (ad1->hmmto   != ad2->hmmto)                      return eslFAIL;
  if (ad1->M       != ad2->M)                          return eslFAIL;

  if (esl_strcmp(ad1->sqname,  ad2->sqname)  != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->sqacc,   ad2->sqacc)   != eslOK) return eslFAIL;
  if (esl_strcmp(ad1->sqdesc,  ad2->sqdesc)  != eslOK) return eslFAIL;
  if (ad1->sqfrom != ad2->sqfrom)                      return eslFAIL;
  if (ad1->sqto   != ad2->sqto)                        return eslFAIL;
  if (ad1->M      != ad2->M)                           return eslFAIL;

  return eslOK;
}
