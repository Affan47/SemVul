addscore (int num)
{
  gchar string[20];
  int i = 0;
  int retval;

  while ((sctab[i].num != num) && (sctab[i].num != 0))
    i++;
  if (sctab[i].num == 0) {
    num-=5;
    retval = sctab[num%5].score + 72 * (num/5) + (num-5)*24 ;
  } else
    retval = sctab[i].score;

  score += retval;
  g_snprintf (string, 19, "%d", score);
  gtk_label_set_text (GTK_LABEL (scorelabel), string);

  return retval;
}
