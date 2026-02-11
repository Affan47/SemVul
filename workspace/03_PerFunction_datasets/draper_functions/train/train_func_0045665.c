publishExtra(JDnsPublishExtra *extra)
	{
		Q_ASSERT(!extraList.contains(extra));

		connect(&extra->pub, SIGNAL(resultsReady()), SLOT(pub_extra_ready()));
		extraList += extra;


		if(!have_srv)
			return;

		doPublishExtra(extra);
	}
