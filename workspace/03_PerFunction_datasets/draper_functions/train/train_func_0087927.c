ip_registry_update_free_targets(struct IPRegistryEntry* entry)
{
  unsigned int free_targets = STARTTARGETS;

  if (entry->target) {
    free_targets = entry->target->count + (CONNECTED_SINCE(entry->last_connect) / TARGET_DELAY);
    if (free_targets > STARTTARGETS)
      free_targets = STARTTARGETS;
    entry->target->count = free_targets;
  }
  return free_targets;
}
