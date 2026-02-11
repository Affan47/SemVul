share_userfileq(int idx, char *par)
{
  int ok = 1, i, bfl = bot_flags(dcc[idx].user);

  flush_tbuf(dcc[idx].nick);
  if (bfl & BOT_AGGRESSIVE)
    dprintf(idx, "s un I have you marked for Aggressive sharing.\n");
  else if (!(bfl & BOT_PASSIVE))
    dprintf(idx, "s un You are not marked for sharing with me.\n");
  else if (min_share > dcc[idx].u.bot->numver)
    dprintf(idx,
            "s un Your version is not high enough, need v%d.%d.%d\n",
            (min_share / 1000000), (min_share / 10000) % 100,
            (min_share / 100) % 100);
  else {
    for (i = 0; i < dcc_total; i++)
      if (dcc[i].type->flags & DCT_BOT) {
        if ((dcc[i].status & STAT_SHARE) &&
            (dcc[i].status & STAT_AGGRESSIVE) && (i != idx)) {
          ok = 0;
          break;
        }
      }
    if (!ok)
      dprintf(idx, "s un Already sharing.\n");
    else {
      if (dcc[idx].u.bot->numver >= min_uffeature)
        dprintf(idx, "s uy %s\n", uf_features_dump(idx));
      else
        dprintf(idx, "s uy\n");

      dcc[idx].status |= STAT_SHARE | STAT_GETTING | STAT_AGGRESSIVE;
      putlog(LOG_BOTS, "*", "Downloading user file from %s", dcc[idx].nick);
    }
  }
}
