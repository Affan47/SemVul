splitOffId(StringC &sysid, StringC &id)
{
  id.resize(0);
  for (size_t i = sysid.size(); i > 0; i--) {
    if (sysid[i - 1] == '#') {
      id.assign(sysid.data() + i,
		sysid.size() - i);
      sysid.resize(i - 1);
      break;
    }
  }
}
