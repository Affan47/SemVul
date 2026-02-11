mk_frame(Sexp* var, Sexp* val, Frame* fp)
{
  if (var->type != 0)
    readerror("You cannot define variable that is not Atom.");
  if (fp == NULL)
    readerror("No room for new definition.");

  fp->var = var;
  fp->val = val;
  fp->next = NULL;
}
