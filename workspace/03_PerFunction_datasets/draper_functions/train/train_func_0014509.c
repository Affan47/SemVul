get_groups () const
{
  std::set<std::string> groups;

  switch (m_type) {
  case RECEIVED:
    groups.insert (_("Received"));
    break;
  case PLACED:
    groups.insert (_("Placed"));
    break;
  case MISSED:
    groups.insert (_("Missed"));
    break;

  default:
    groups.insert ("AIE!!");
  }

  return groups;
}
