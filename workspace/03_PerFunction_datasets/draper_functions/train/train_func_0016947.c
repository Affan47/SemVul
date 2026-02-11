add_to_list(struct bsslist *bsl, const u_char *bssid) {
  struct bsslist *new, *search;

  new= malloc(sizeof(struct bsslist));
  new->bssid = malloc(6);

  memcpy(new->bssid, bssid, 6);
  new->next = NULL;
  new->beacon_saved = 0x00;

  if (bsl == NULL) {
    return new;
  } else {
    search = bsl;
    while (search->next) search = search->next;
    search->next = new;
    return bsl;
  }
}
