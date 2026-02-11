dump_status ()
{
  slog (L_NOTICE, _("node %s (id %d)"), conf->nodename, conf->id);
  slog (L_NOTICE, _("  connectmode %d (%d) / sockaddr %s / minor %d"),
        connectmode, conf->connectmode, (const char *)si, (int)prot_minor);
  slog (L_NOTICE, _("  ictx/octx %08lx/%08lx / oseqno %d / retry_cnt %d"),
        (long)ictx, (long)octx, (int)oseqno, (int)retry_cnt);
}
