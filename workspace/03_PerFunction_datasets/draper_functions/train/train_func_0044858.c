share_killuser(int idx, char *par)
{
  struct userrec *u;


  if ((dcc[idx].status & STAT_SHARE) && !private_user &&
      (u = get_user_by_handle(userlist, par)) &&
      !(u->flags & USER_UNSHARED) &&
      !((u->flags & USER_BOT) && (bot_flags(u) & BOT_SHARE))) {
    noshare = 1;
    if (deluser(par)) {
      shareout_but(NULL, idx, "k %s\n", par);
      putlog(LOG_CMDS, "*", "%s: killuser %s", dcc[idx].nick, par);
    }
    noshare = 0;
  }
}
