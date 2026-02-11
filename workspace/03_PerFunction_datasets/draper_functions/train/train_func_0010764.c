is_an_entry_guard(const char *digest)
{
  SMARTLIST_FOREACH(entry_guards, entry_guard_t *, entry,
                    if (tor_memeq(digest, entry->identity, DIGEST_LEN))
                      return entry;
                   );
  return NULL;
}
