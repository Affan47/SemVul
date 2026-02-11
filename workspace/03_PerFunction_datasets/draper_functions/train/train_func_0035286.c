free_notation(struct notation *notation)
{
  while(notation)
    {
      struct notation *n=notation;

      xfree(n->name);
      xfree(n->value);
      xfree(n->altvalue);
      xfree(n->bdat);
      notation=n->next;
      xfree(n);
    }
}
