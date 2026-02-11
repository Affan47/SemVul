is_supported_uri (const std::string uri) const
{
  boost::shared_ptr<Ekiga::PresenceCore> presence_core = core.get<Ekiga::PresenceCore> ("presence-core");

  return presence_core->is_supported_uri (uri);
}
