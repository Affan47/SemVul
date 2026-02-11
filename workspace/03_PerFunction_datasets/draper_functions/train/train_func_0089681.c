unfetch_presence (const std::string uri)
{
  uri_infos[uri].count--;

  if (uri_infos[uri].count <= 0) {

    uri_infos.erase (uri_infos.find (uri));

    for (std::list<boost::shared_ptr<PresenceFetcher> >::iterator iter
	   = presence_fetchers.begin ();
	 iter != presence_fetchers.end ();
	 ++iter)
      (*iter)->unfetch (uri);
  }
}
