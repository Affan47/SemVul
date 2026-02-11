process_dbfile(struct cfg_s *cfg, char *dbfile, int dbfmt)
{
  ESL_SQ     *sq    = esl_sq_CreateDigital(cfg->abc);
  int         status;
  int         nread;
  int         nrequired;


  status = esl_sqfile_OpenDigital(cfg->abc, dbfile, dbfmt, NULL, &(cfg->dbfp));
  if      (status == eslENOTFOUND) esl_fatal("No such file %s", dbfile);
  else if (status == eslEFORMAT)   esl_fatal("Format of seqfile %s unrecognized.", dbfile);
  else if (status == eslEINVAL)    esl_fatal("Can't autodetect stdin or .gz.");
  else if (status != eslOK)        esl_fatal("Open failed, code %d.", status);


  nread = 0;
  nrequired = ((cfg->negL / cfg->negchunkL) + 1) * cfg->nneg;

  while ((nread < nrequired) &&
	 ((status = esl_sqio_ReadInfo(cfg->dbfp, sq)) == eslOK)) {
    if(sq->L > cfg->negchunkL) nread++;
    esl_sq_Reuse(sq);
  }
  if (nread < nrequired) {
    if(status == eslEOF) esl_fatal("Only read %d seqs of length %d in seq db, %d required", nread, cfg->negchunkL, nrequired);
    else                 esl_fatal("Something went wrong with reading the seq db");
  }
  esl_sqfile_Position(cfg->dbfp, 0);


  if (esl_sqfile_OpenSSI(cfg->dbfp, NULL) != eslOK) esl_fatal("Failed to open SSI index file");

  cfg->db_nseq = cfg->dbfp->data.ascii.ssi->nprimary;

  esl_sq_Destroy(sq);
  return eslOK;
}
