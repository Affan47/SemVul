find_chasing(struct Client *client_p, struct Client *source_p, const char *user, int *chasing)
{
  struct Client *who = find_person(client_p, user);

  if (chasing)
    *chasing = 0;

  if (who)
    return(who);

  if (IsDigit(*user))
    return(NULL);

  if ((who = get_history(user,
			(time_t)ConfigFileEntry.kill_chase_time_limit))
			 == NULL)
  {
    sendto_one(source_p, form_str(ERR_NOSUCHNICK),
               me.name, source_p->name, user);
    return(NULL);
  }

  if (chasing)
    *chasing = 1;

  return(who);
}
