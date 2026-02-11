sendxdlqueue (void)
{
  char *tempstr;
  char *user;
  int len;
  userinput ui;

  updatecontext();

  if (!irlist_size(&gdata.xlistqueue))
    {
      return;
    }

  len = 0;
  user = irlist_get_head(&gdata.xlistqueue);
  while (user)
    {
      len += strlen(user) + 1;
      user = irlist_get_next(user);
    }

  tempstr = mycalloc(len);

  len = 0;
  user = irlist_get_head(&gdata.xlistqueue);
  strcpy(tempstr+len, user);
  len += strlen(tempstr+len);

  user = irlist_delete(&gdata.xlistqueue, user);
  while (user)
    {
      strcpy(tempstr+len, ",");
      len += strlen(tempstr+len);
      strcpy(tempstr+len, user);
      len += strlen(tempstr+len);

      user = irlist_delete(&gdata.xlistqueue, user);
    }

  if (gdata.nolisting > gdata.curtime)
    {
      ioutput(CALLTYPE_NORMAL,OUT_S|OUT_D,COLOR_YELLOW,"Not Sending XDCC LIST to: %s (nolist set)",tempstr);

      notice(tempstr,
             "The Owner Has Requested That No Lists Be Sent In The Next %li Minute%s",
             1+(gdata.nolisting-gdata.curtime)/60,
             ((1+(gdata.nolisting-gdata.curtime)/60) != 1 ? "s" : ""));
    }
  else
    {
      ioutput(CALLTYPE_NORMAL,OUT_S|OUT_D,COLOR_YELLOW,"Sending XDCC LIST to: %s",tempstr);

      u_fillwith_msg(&ui,tempstr,"A A A A A xdl");
      ui.method = method_xdl_user_notice;
      u_parseit(&ui);
    }

  mydelete(tempstr);
}
