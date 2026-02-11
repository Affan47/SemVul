lib3ds_lin1_track_insert(Lib3dsLin1Track *track, Lib3dsLin1Key *key)
{
  ASSERT(track);
  ASSERT(key);
  ASSERT(!key->next);

  if (!track->keyL) {
    track->keyL=key;
    key->next=0;
  }
  else {
    Lib3dsLin1Key *k,*p;

    for (p=0,k=track->keyL; k!=0; p=k, k=k->next) {
      if (k->tcb.frame>key->tcb.frame) {
        break;
      }
    }
    if (!p) {
      key->next=track->keyL;
      track->keyL=key;
    }
    else {
      key->next=k;
      p->next=key;
    }

    if (k && (key->tcb.frame==k->tcb.frame)) {
      key->next=k->next;
      lib3ds_lin1_key_free(k);
    }
  }
}
