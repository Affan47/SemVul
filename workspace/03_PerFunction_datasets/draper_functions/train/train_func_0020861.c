output_word_list(FILE *fp)
{
  word_type *wp;

  fprintf(fp, "# word id list\n");
  fprintf(fp, "<id version=2>\n");
  fprintf(fp, "# name                  id      start state\n");
  fprintf(fp, "#----------------------+-------+-----------\n");

  for (wp = word_list; wp != NULL; wp = wp->next)
    fprintf(fp, "%-23s %-7u %u\n", wp->pname, wp->id,
	    wp->start == NULL ? 0 : wp->start->id);

  fprintf(fp, "</id>\n");
}
