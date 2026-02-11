rtp_source_add_conflicting_address (RTPSource * src,
    GSocketAddress * address, GstClockTime time)
{
  RTPConflictingAddress *new_conflict;

  new_conflict = g_new0 (RTPConflictingAddress, 1);

  new_conflict->address = G_SOCKET_ADDRESS (g_object_ref (address));
  new_conflict->time = time;

  src->conflicting_addresses = g_list_prepend (src->conflicting_addresses,
      new_conflict);
}
