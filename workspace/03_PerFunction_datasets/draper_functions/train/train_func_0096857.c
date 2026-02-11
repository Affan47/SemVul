Populate(mdo::Item* node, bool checkDirty)
{
  if(checkDirty)
    {
    node->SetDirty(IsResourceDirty(GetUuid(
      midasResourceType::ITEM, node->GetId())));
    }
  std::stringstream query;
  query << "SELECT bitstream.bitstream_id, bitstream.name, resource_uuid.uuid "
    "FROM bitstream, resource_uuid WHERE resource_uuid.resource_id=bitstream.bitstream_id "
    "AND resource_uuid.resource_type_id='" << midasResourceType::BITSTREAM << "' AND "
    "bitstream.bitstream_id IN (SELECT bitstream_id FROM item2bitstream WHERE item_id="
    << node->GetId() << ")";
  this->Database->ExecuteQuery(query.str().c_str());

  std::vector<mdo::Bitstream*> bitstreams;
  while(this->Database->GetNextRow())
    {
    mdo::Bitstream* bitstream = new mdo::Bitstream;
    bitstream->SetId(this->Database->GetValueAsInt(0));
    bitstream->SetName(this->Database->GetValueAsString(1));
    bitstream->SetUuid(this->Database->GetValueAsString(2));
    node->AddBitstream(bitstream);
    bitstreams.push_back(bitstream);
    }

  if(checkDirty)
    {
    for(std::vector<mdo::Bitstream*>::iterator i = bitstreams.begin();
        i != bitstreams.end(); ++i)
      {
      (*i)->SetDirty(IsResourceDirty(GetUuid(
        midasResourceType::BITSTREAM, (*i)->GetId())));
      }
    }
}
