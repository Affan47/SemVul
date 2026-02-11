ira_print_disposition (FILE *f)
{
  int i, n, max_regno;
  ira_allocno_t a;
  basic_block bb;

  fprintf (f, "Disposition:");
  max_regno = max_reg_num ();
  for (n = 0, i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    for (a = ira_regno_allocno_map[i];
	 a != NULL;
	 a = ALLOCNO_NEXT_REGNO_ALLOCNO (a))
      {
	if (n % 4 == 0)
	  fprintf (f, "\n");
	n++;
	fprintf (f, " %4d:r%-4d", ALLOCNO_NUM (a), ALLOCNO_REGNO (a));
	if ((bb = ALLOCNO_LOOP_TREE_NODE (a)->bb) != NULL)
	  fprintf (f, "b%-3d", bb->index);
	else
	  fprintf (f, "l%-3d", ALLOCNO_LOOP_TREE_NODE (a)->loop_num);
	if (ALLOCNO_HARD_REGNO (a) >= 0)
	  fprintf (f, " %3d", ALLOCNO_HARD_REGNO (a));
	else
	  fprintf (f, " mem");
      }
  fprintf (f, "\n");
}
