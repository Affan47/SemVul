sort_unsortall(sort_info_t *i)
{


  if (i->lastbucket>2000) {
    memset(i->head,0,65536*sizeof(sort_link_t *));
  } else {
    long b;
    for (b=0; b<i->lastbucket; b++)
      i->head[i->bucketusage[b]]=NULL;
  }

  i->lastbucket=0;
  i->sortbegin=-1;


}
