URIPresentity (Ekiga::ServiceCore &_core,
				     std::string name_,
				     std::string uri_,
				     std::set<std::string> groups_)
  : core(_core), name(name_), uri(uri_), presence("unknown"), groups(groups_)
{
  boost::shared_ptr<Ekiga::PresenceCore> presence_core = core.get<Ekiga::PresenceCore> ("presence-core");
  presence_core->presence_received.connect (boost::bind (&Ekiga::URIPresentity::on_presence_received, this, _1, _2));
  presence_core->status_received.connect (boost::bind (&Ekiga::URIPresentity::on_status_received, this, _1, _2));
  presence_core->fetch_presence (uri);
}
