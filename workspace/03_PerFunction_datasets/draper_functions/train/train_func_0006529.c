create_onecell_colorlegend(float *col, int nres, int nres_masked, int do_separator, int do_no_vspace)
{
  int status;
  OneCellColorLegend_t *occl;

  ESL_ALLOC(occl, sizeof(OneCellColorLegend_t));


  esl_vec_FSet(occl->col, NCMYK, 0.);
  occl->text  = NULL;
  occl->celltext = NULL;
  occl->procname = NULL;
  occl->procstack = NULL;
  occl->nprocstack = 0;


  esl_vec_FCopy(col, NCMYK, occl->col);

  occl->nres         = nres;
  occl->nres_masked  = nres_masked;
  occl->do_separator = do_separator;
  occl->do_no_vspace = do_no_vspace;

  return occl;

 ERROR: esl_fatal("create_onecell_colorlegend(): memory allocation error.");
  return NULL;
}
