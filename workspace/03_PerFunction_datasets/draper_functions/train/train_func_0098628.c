try_initialize_more (Ekiga::ServiceCore& core,
			    int* ,
			    char** [])
  {
    boost::shared_ptr<Ekiga::PresenceCore> presence_core = core.get<Ekiga::PresenceCore> ("presence-core");
    boost::shared_ptr<Ekiga::CallCore> call_core = core.get<Ekiga::CallCore> ("call-core");
    boost::shared_ptr<Ekiga::PersonalDetails> details = core.get<Ekiga::PersonalDetails> ("personal-details");

    if (presence_core && call_core && details) {

      boost::shared_ptr<Avahi::PresencePublisher> publisher (new Avahi::PresencePublisher (core, *details, *call_core));
      if (core.add (publisher)) {

	presence_core->add_presence_publisher (publisher);
	result = true;
      }

      boost::shared_ptr<Avahi::Cluster> cluster (new Avahi::Cluster (core));
      if (core.add (cluster)) {

	presence_core->add_cluster (cluster);
	result = true;
      }
    }

    return result;
  }
