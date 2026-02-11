sqncbi_Open(ESL_SQNCBI_DATA *ncbi, char *filename)
{
  int    status  = eslOK;
  char  *name    = NULL;


  status = sqncbi_DbOpen(ncbi, filename, NCBI_AMINO_DB);


  if (status == eslENOTFOUND) {
    status = sqncbi_AliasOpen(ncbi, filename, NCBI_AMINO_DB);
  }


  if (status == eslENOTFOUND) {
    status = sqncbi_DbOpen(ncbi, filename, NCBI_DNA_DB);
  }


  if (status == eslENOTFOUND) {
    status = sqncbi_AliasOpen(ncbi, filename, NCBI_DNA_DB);
  }

  if (status != eslOK) goto ERROR;


  ESL_ALLOC(ncbi->hdr_indexes, sizeof(uint32_t) * INDEX_TABLE_SIZE);
  ESL_ALLOC(ncbi->seq_indexes, sizeof(uint32_t) * INDEX_TABLE_SIZE);


  if (ncbi->alphatype == eslDNA) {
    ncbi->amb_off = ncbi->seq_off + sizeof(uint32_t) * (ncbi->num_seq + 1);
    ESL_ALLOC(ncbi->amb_indexes, sizeof(uint32_t) * INDEX_TABLE_SIZE);
  }

  ncbi->hdr_alloced = INIT_HDR_BUFFER_SIZE;
  ESL_ALLOC(ncbi->hdr_buf, sizeof(char) * INIT_HDR_BUFFER_SIZE);


  fgetc(ncbi->fppsq);

  if (name != NULL) free(name);
  return eslOK;

 ERROR:
  if (name != NULL) free(name);
  return status;
}
