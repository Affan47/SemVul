FetchByUuid(std::string uuid)
{
  mdo::Object* object = NULL;
  std::stringstream fields;
  fields << "midas.resource.get?uuid=" << uuid;

  std::string idStr, typeStr;
  mws::RestXMLParser parser;
  parser.AddTag("/rsp/id", idStr);
  parser.AddTag("/rsp/type", typeStr);

  mws::WebAPI::Instance()->GetRestAPI()->SetXMLParser(&parser);
  if(mws::WebAPI::Instance()->Execute(fields.str().c_str()))
    {
    int id = atoi(idStr.c_str());
    int type = atoi(typeStr.c_str());

    if(id == 0) return NULL;

    mdo::Community* comm = NULL;
    mdo::Collection* coll = NULL;
    mdo::Item* item = NULL;
    mdo::Bitstream* bitstream = NULL;

    switch(type)
      {
      case midasResourceType::COMMUNITY:
        comm = new mdo::Community();
        comm->SetId(id);
        object = reinterpret_cast<mdo::Object*>(comm);
        break;
      case midasResourceType::COLLECTION:
        coll = new mdo::Collection();
        coll->SetId(id);
        object = reinterpret_cast<mdo::Object*>(coll);
        break;
      case midasResourceType::ITEM:
        item = new mdo::Item();
        item->SetId(id);
        object = reinterpret_cast<mdo::Object*>(item);
        break;
      case midasResourceType::BITSTREAM:
        bitstream = new mdo::Bitstream();
        bitstream->SetId(id);
        object = reinterpret_cast<mdo::Object*>(bitstream);
        break;
      default:
        break;
      }
    }

  return object;
}
