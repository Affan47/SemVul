coolscan_object_feed (Coolscan_t * s)
{
  int ret;
  DBG (10, "Trying to feed object...\n");
  if (!s->asf)
    {
      DBG (10, "\tAutofeeder not present.\n");
      return 0;
    }
  memcpy (s->buffer, object_position.cmd, object_position.size);
  set_OP_autofeed (s->buffer, OP_Feed);
  ret = do_scsi_cmd (s->sfd, s->buffer,
		     object_position.size, NULL, 0);
  wait_scanner (s);
  DBG (10, "Object fed.\n");
  return ret;
}
