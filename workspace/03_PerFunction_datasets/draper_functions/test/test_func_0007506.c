untranslate_sequence(seq)
     Sequence *seq;
{
  Sequence *new_seq;
  Residue *res;
  Residue *new_res;
  int i;


  if ( seq->type != AA_SEQ ) {
    sprintf(ErrorBuffer,
    "untranslate_sequence(): Not an amino acid sequence, not untranslating.");
    ErrorReport(PROGRAM_ERR_LVL);
    sprintf(ErrorBuffer,
	    "                      Returning the original sequence.\n");
    ErrorReport(PROGRAM_ERR_LVL);
    return seq;
  }


  CheckMem(
	   new_seq = (Sequence *) malloc(sizeof(Sequence))
	   );


  CheckMem(
	   new_res = (Residue *) calloc((seq->length)*3,
					sizeof(Residue))
	   );
  new_seq->length = new_seq->max_length = (seq->length) * 3;
  new_seq->type = NA_SEQ;
  new_seq->position = seq->position;
  strcpy(new_seq->name, seq->name);
  strcpy(new_seq->info, seq->info);


  res = seq->sequence;
  for (i=0; i < seq->length; i++)
  {
     aa2codon(res[i], &new_res[i*3], &new_res[i*3+1], &new_res[i*3+2]);
  }


  strncpy(new_seq->name, seq->name, SMALL_BUFF_LENGTH);
  strncpy(new_seq->info, seq->info, SMALL_BUFF_LENGTH);

  new_seq->sequence = new_res;

  return new_seq;

}
