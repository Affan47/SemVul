ms_svinfo(struct Client *client_p, struct Client *source_p,
	  int parc, char *parv[])
{
  time_t deltat;
  time_t theirtime;

  if (MyConnect(source_p) && IsUnknown(source_p))
  {
    exit_client(source_p, source_p, "Need SERVER before SVINFO");
    return;
  }

  if (!IsServer(source_p) || !MyConnect(source_p) || parc < 5)
    return;

  if (TS_CURRENT < atoi(parv[2]) || atoi(parv[1]) < TS_MIN)
    {


      sendto_realops_flags(UMODE_ALL, L_ADMIN,
            "Link %s dropped, wrong TS protocol version (%s,%s)",
            get_client_name(source_p, SHOW_IP), parv[1], parv[2]);
      sendto_realops_flags(UMODE_ALL, L_OPER,
                 "Link %s dropped, wrong TS protocol version (%s,%s)",
                 get_client_name(source_p, MASK_IP), parv[1], parv[2]);
      exit_client(source_p, source_p, "Incompatible TS version");
      return;
    }


  set_time();
  theirtime = atol(parv[4]);
  deltat = abs(theirtime - CurrentTime);

  if (deltat > ConfigFileEntry.ts_max_delta)
    {
      sendto_realops_flags(UMODE_ALL, L_ADMIN,
          "Link %s dropped, excessive TS delta (my TS=%lu, their TS=%lu, delta=%d)",
          get_client_name(source_p, SHOW_IP),
          (unsigned long) CurrentTime,
          (unsigned long) theirtime,
          (int) deltat);
      sendto_realops_flags(UMODE_ALL, L_OPER,
          "Link %s dropped, excessive TS delta (my TS=%lu, their TS=%lu, delta=%d)",
           get_client_name(source_p, MASK_IP),
           (unsigned long) CurrentTime,
           (unsigned long) theirtime,
           (int) deltat);
      ilog(L_NOTICE,
          "Link %s dropped, excessive TS delta (my TS=%lu, their TS=%lu, delta=%d)",
          get_client_name(source_p, SHOW_IP),
          (unsigned long) CurrentTime,
          (unsigned long) theirtime,
          (int) deltat);
      exit_client(source_p, source_p, "Excessive TS delta");
      return;
    }

  if (deltat > ConfigFileEntry.ts_warn_delta)
    {
      sendto_realops_flags(UMODE_ALL, L_ALL,
                "Link %s notable TS delta (my TS=%lu, their TS=%lu, delta=%d)",
                source_p->name,
                (unsigned long) CurrentTime,
                (unsigned long) theirtime,
                (int) deltat);
    }
}
