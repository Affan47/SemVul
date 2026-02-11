mo_modlist(struct Client *client_p, struct Client *source_p,
	   int parc, char *parv[])
{
  const dlink_node *ptr = NULL;

  if (!IsAdmin(source_p))
  {
    sendto_one(source_p, form_str(ERR_NOPRIVILEGES),
               me.name, source_p->name);
    return;
  }

  DLINK_FOREACH(ptr, mod_list.head)
  {
    const struct module *modp = ptr->data;

    if (parc > 1 && !match(parv[1], modp->name))
      continue;

    sendto_one(source_p, form_str(RPL_MODLIST), me.name, parv[0],
               modp->name, modp->handle,
               modp->version, modp->core?"(core)":"");
  }

  sendto_one(source_p, form_str(RPL_ENDOFMODLIST),
             me.name, source_p->name);
}
