global_worklist_set(struct global_worklist *pgwl,
                         const struct worklist *pwl)
{
  if (pgwl && pgwl->status == STATUS_WORKLIST && pwl) {
    worklist_copy(&pgwl->worklist, pwl);
    return TRUE;
  }
  return FALSE;
}
