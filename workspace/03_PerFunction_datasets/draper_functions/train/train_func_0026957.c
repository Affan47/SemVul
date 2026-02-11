remove ()
{
  boost::shared_ptr<Ekiga::PresenceCore> presence_core = core.get<Ekiga::PresenceCore> ("presence-core");
  presence_core->unfetch_presence (get_uri ());

  xmlUnlinkNode (node);
  xmlFreeNode (node);

  trigger_saving ();
  removed ();
}
