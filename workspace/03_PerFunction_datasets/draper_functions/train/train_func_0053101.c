hSeekChannel(const char *name)
{
  HASHREGS hashv = strhash(name);
  struct Channel *chptr = channelTable[hashv];

  if (chptr) {
    if (0 != ircd_strcmp(name, chptr->chname)) {
      struct Channel* prev;
      while (prev = chptr, chptr = chptr->hnext) {
        if (0 == ircd_strcmp(name, chptr->chname)) {
          prev->hnext = chptr->hnext;
          chptr->hnext = channelTable[hashv];
          channelTable[hashv] = chptr;
          break;
        }
      }
    }
  }
  return chptr;

}
