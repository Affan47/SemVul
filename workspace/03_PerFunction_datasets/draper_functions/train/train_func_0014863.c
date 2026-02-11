freehist(histhash *hash) {
  int i=0;
  histnode *destroyer, *destroyernext;
  for (; i < hash->hashsize; i++) {
    destroyer = hash->history[i];
    while (destroyer) {
      destroyernext = destroyer->next;
      free(destroyer);
      destroyer = destroyernext;
    }
  }
  free(hash->history);
  free(hash);
}
