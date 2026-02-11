search_name_for_uri (const std::string uri)
{
  std::string result;

  possible_names.clear ();

  contact_core->visit_sources (boost::bind (&name_from_uri_helper::on_visit_sources, this, _1, uri));
  presence_core->visit_clusters (boost::bind (&name_from_uri_helper::on_visit_clusters, this, _1, uri));

  if (possible_names.empty ())
    result = _("Unknown");
  else
    result = *(possible_names.begin ());

  return result;
}
