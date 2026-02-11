bgav_mkv_tag_free(bgav_mkv_tag_t * t)
  {
  int i;

  for(i = 0; i < t->num_st; i++)
    bgav_mkv_simple_tag_free(t->st + i);
  MY_FREE(t->st);
  bgav_mkv_targets_free(&t->targets);
  }
