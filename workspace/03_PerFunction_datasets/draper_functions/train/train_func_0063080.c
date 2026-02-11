total_record_delete(total_record *p)
{
  if (p != NULL)
  {
    if (p->stage_id != NULL)
      free(p->stage_id);
    if (p->stage_score != NULL)
      free(p->stage_score);
    if (p->stage_cleared != NULL)
      free(p->stage_cleared);

    free(p);
  }
}
