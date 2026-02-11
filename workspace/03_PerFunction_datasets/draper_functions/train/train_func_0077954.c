fprint_formula(FILE *fp, Formula f)
{
  if (f->type == ATOM_FORM) {

    fprint_term(fp, f->atom);

  }
  else if (f->type == NOT_FORM) {

    fprintf(fp, "%s ", not_sym());
    fprint_formula(fp, f->kids[0]);

  }
  else if (f->type == IFF_FORM) {
    fprintf(fp, "(");
    fprint_formula(fp, f->kids[0]);
    fprintf(fp, " %s ", iff_sym());
    fprint_formula(fp, f->kids[1]);
    fprintf(fp, ")");
  }
  else if (f->type == IMP_FORM) {
    fprintf(fp, "(");
    fprint_formula(fp, f->kids[0]);
    fprintf(fp, " %s ", imp_sym());
    fprint_formula(fp, f->kids[1]);
    fprintf(fp, ")");
  }
  else if (f->type == IMPBY_FORM) {
    fprintf(fp, "(");
    fprint_formula(fp, f->kids[0]);
    fprintf(fp, " %s ", impby_sym());
    fprint_formula(fp, f->kids[1]);
    fprintf(fp, ")");
  }
  else if (quant_form(f)) {
    fprintf(fp, "(%s %s ", f->type==ALL_FORM ? all_sym() : exists_sym(), f->qvar);
    fprint_formula(fp, f->kids[0]);
    fprintf(fp, ")");
  }
  else if (f->type == AND_FORM || f->type == OR_FORM) {
    if (f->arity == 0)
      fprintf(fp, "%s", f->type == AND_FORM ? true_sym() : false_sym());
    else {
      int i;
      fprintf(fp, "(");
      for (i = 0; i < f->arity; i++) {
	fprint_formula(fp, f->kids[i]);
	if (i < f->arity-1)
	  fprintf(fp, " %s ", f->type == AND_FORM ? and_sym() : or_sym());
      }
      fprintf(fp, ")");
    }
  }
}
