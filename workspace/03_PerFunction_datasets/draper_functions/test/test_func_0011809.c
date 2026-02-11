get_table(dxml_element *b_parent)
{
  int i;
  int width;
  dxml_element *row, *entry, *b = b_parent -> child;
  int columns=atoi(getatrstring (dxml_get_element_byname(b, "tgroup"), "cols"));
  printf ("\\begin{table}\n"
	  "\\caption{%s}\n",
	  dxml_get_PCDATA_bysimplepath(b,"title"));
  maybe_label(b_parent);

  width=12/columns;
  printf ("\\begin{tabular}{p{%icm}", width);
  for (i=0; i< columns - 1 ; i++)
    printf ("|p{%icm}", width);
  printf ("}\n\\hline\n\\hline\n");
  for (row = dxml_get_element_bysimplepath(b, "tgroup/tbody/row"); row; row = row->next )
    {
      for (entry = row->child; entry; entry = entry -> next)
	{
	  get_paratype(entry->child,0);
	  if (entry->next)
	    printf (" & ");

	}

      printf ("\\\\\n");
    }
  printf (
	  "\\hline\n\\hline\n"
	  "\\end{tabular}\n"
	  "\\end{table}\n"
	  );
  return 0;
}
