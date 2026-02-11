sp15c_free_scanner (struct sp15c *s)
{
  int ret;
  DBG (10, "sp15c_free_scanner\n");
#if 0


  ret = sp15c_object_discharge (s);
  if (ret)
    return ret;
#endif

  wait_scanner (s);

  ret = do_scsi_cmd (s->sfd, release_unitB.cmd, release_unitB.size, NULL, 0);
  if (ret)
    return ret;

  DBG (10, "sp15c_free_scanner: ok\n");
  return ret;
}
