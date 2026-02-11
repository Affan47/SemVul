get_status () const
{
  std::string result = "";

  if ( !infos.empty ()) {

    infos_type::const_iterator iter = infos.begin ();
    ResourceInfo best = iter->second;
    ++iter;
    while (iter != infos.end ()) {

      if (iter->second.priority > best.priority) {

	best = iter->second;
      }
      ++iter;
    }
    result = best.status;
  }

  return result;
}
