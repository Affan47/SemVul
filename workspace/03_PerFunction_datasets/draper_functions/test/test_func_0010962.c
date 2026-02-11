allocateSeqdata (FM_METADATA *meta, ESL_SQ *sq, int numseqs, int *allocedseqs) {
  int length;
  int status = eslOK;
  if (numseqs == *allocedseqs) {
    *allocedseqs *= 2;
  }

  if (numseqs == 0 || numseqs == *allocedseqs) {
    ESL_REALLOC (meta->seq_data, *allocedseqs * sizeof(FM_SEQDATA));
    if (meta->seq_data == NULL )
      esl_fatal("unable to allocate memory to store FM meta data\n");
  }


  length = strlen(sq->name);
  meta->seq_data[numseqs].name_length = length;
  ESL_ALLOC (meta->seq_data[numseqs].name, (1+length) * sizeof(char));

  length = strlen(sq->acc);
  meta->seq_data[numseqs].acc_length = length;
  ESL_ALLOC (meta->seq_data[numseqs].acc, (1+length) * sizeof(char));

  length = strlen(sq->source);
  meta->seq_data[numseqs].source_length = length;
  ESL_ALLOC (meta->seq_data[numseqs].source, (1+length) * sizeof(char));

  length = strlen(sq->desc);
  meta->seq_data[numseqs].desc_length = length;
  ESL_ALLOC (meta->seq_data[numseqs].desc, (1+length) * sizeof(char));


  if (meta->seq_data[numseqs].name == NULL || meta->seq_data[numseqs].acc == NULL || meta->seq_data[numseqs].source == NULL || meta->seq_data[numseqs].desc == NULL)
    esl_fatal("unable to allocate memory to store FM meta data\n");

  return eslOK;

ERROR:
  return status;
}
