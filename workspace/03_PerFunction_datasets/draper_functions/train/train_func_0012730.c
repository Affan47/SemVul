ip_registry_find(const struct irc_in_addr *ip)
{
  struct irc_in_addr canon;
  struct IPRegistryEntry* entry;
  ip_registry_canonicalize(&canon, ip);
  entry = hashTable[ip_registry_hash(&canon)];
  for ( ; entry; entry = entry->next) {
    int bits = (canon.in6_16[0] == htons(0x2002)) ? 48 : 64;
    if (ipmask_check(&canon, &entry->addr, bits))
      break;
  }
  return entry;
}
