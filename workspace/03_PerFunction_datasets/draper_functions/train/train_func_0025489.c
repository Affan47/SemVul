make_xml (RepoXMLNode parent) {

  RepoXMLNode joinpoints = parent.make_child ("joinpoint-list");

  for (Map::iterator curr = _map.begin (); curr != _map.end (); ++curr) {
    RepoXMLNode jpn = joinpoints.make_child ("joinpoint");

    const RepoPosKey &key   = (*curr).first;
    key.make_xml (jpn);

    const Data &data = (*curr).second;
    string adv;
    for (set<int>::const_iterator curr = data._advice.begin ();
	 curr != data._advice.end (); ++curr) {
      if (curr != data._advice.begin ())
	adv += ",";
      adv += idstr (*curr);
    }

    jpn.set_int_prop ("id", data._id);
    jpn.set_str_prop ("type", data._type.c_str ());
    jpn.set_str_prop ("signature", data._signature.c_str ());
    jpn.set_str_prop ("advice", adv.c_str ());
    jpn.set_int_prop ("lines", data._lines);
  }
}
