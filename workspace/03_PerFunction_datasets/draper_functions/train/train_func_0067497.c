remove_vote(struct vote *pvote)
{
  if (!vote_list || !pvote) {
    return;
  }

  vote_list_remove(vote_list, pvote);
  lsend_vote_remove(NULL, pvote);
  free_vote(pvote);
}
