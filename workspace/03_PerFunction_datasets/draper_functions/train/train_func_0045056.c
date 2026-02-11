opt_reg_note(struct opt_odb_t *odb,
	     char *note_str)
{
  struct opt_note_t *note, *elt, *prev;

  note = (struct opt_note_t *)calloc(1, sizeof(struct opt_note_t));
  if (!note)
    fatal("out of virtual memory");


  note->next = NULL;
  note->note = note_str;


  for (prev=NULL, elt=odb->notes; elt != NULL; prev=elt, elt=elt->next)
    ;

  if (prev != NULL)
    prev->next = note;
  else
    odb->notes = note;
  note->next = NULL;
}
