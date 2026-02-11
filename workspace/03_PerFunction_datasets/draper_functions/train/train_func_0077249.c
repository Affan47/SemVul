GetParentId(int type, int id)
{
  std::stringstream query;

  switch(type)
    {
    case midasResourceType::BITSTREAM:
      query << "SELECT item_id FROM item2bitstream WHERE bitstream_id='"
        << id << "'";
      break;
    case midasResourceType::COMMUNITY:
      query << "SELECT parent_comm_id FROM community2community WHERE "
        "child_comm_id='" << id << "'";
      break;
    case midasResourceType::COLLECTION:
      query << "SELECT community_id FROM community2collection WHERE "
        "collection_id='" << id << "'";
      break;
    case midasResourceType::ITEM:
      query << "SELECT collection_id FROM collection2item WHERE item_id='"
        << id << "'";
      break;
    default:
      return 0;
    }
  this->Database->ExecuteQuery(query.str().c_str());
  int parentId = (this->Database->GetNextRow() ?
    this->Database->GetValueAsInt(0) : 0);
  while(this->Database->GetNextRow());
  return parentId;
}
