gen_split (rtx split, int lineno)
{
  struct data *d = XNEW (struct data);
  int i;

  d->code_number = next_code_number;
  d->index_number = next_index_number;
  d->filename = read_md_filename;
  d->lineno = lineno;
  d->name = 0;


  d->next = 0;
  *idata_end = d;
  idata_end = &d->next;

  max_opno = -1;
  num_dups = 0;
  memset (d->operand, 0, sizeof (d->operand));


  for (i = 0; i < XVECLEN (split, 0); i++)
    scan_operands (d, XVECEXP (split, 0, i), 0, 0);

  d->n_operands = max_opno + 1;
  d->n_dups = 0;
  d->n_alternatives = 0;
  d->template_code = 0;
  d->output_format = INSN_OUTPUT_FORMAT_NONE;

  place_operands (d);
}
