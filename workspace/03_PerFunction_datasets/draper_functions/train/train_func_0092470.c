bgav_chapter_list_destroy(bgav_chapter_list_t * list)
  {
  int i;
  for(i = 0; i < list->num_chapters; i++)
    if(list->chapters[i].name) free(list->chapters[i].name);
  if(list->chapters)
    free(list->chapters);
  free(list);
  }
