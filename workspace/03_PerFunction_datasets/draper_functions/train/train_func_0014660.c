PullBitstream(int parentId)
{
  mws::Bitstream remote;
  mdo::Bitstream* bitstream = new mdo::Bitstream;
  bitstream->SetId(atoi(this->ResourceHandle.c_str()));
  remote.SetWebAPI(mws::WebAPI::Instance());
  remote.SetObject(bitstream);

  this->Progress->SetIndeterminate();
  this->Log->Status("Fetching bitstream information...");
  if(!remote.Fetch())
    {
    std::stringstream text;
    text << "Unable to get bitstream via the web API."
      << std::endl;
    Log->Error(text.str());
    return false;
    }


  if(parentId == NO_PARENT)
    {
    bool recurse = this->Recursive;
    this->Recursive = false;
    std::string handle = this->ResourceHandle;
    this->ResourceHandle = bitstream->GetParent();

    this->PullItem(NO_PARENT);
    this->DatabaseProxy->Open();
    CHANGE_DIR(this->LastDir.c_str());

    this->ResourceHandle = handle;
    this->Recursive = recurse;
    parentId = this->LastId;
    }

  if(bitstream->GetName() == "")
    {
    std::stringstream text;
    text << "Bitstream " << this->ResourceHandle <<
      " does not exist." << std::endl;
    Log->Error(text.str());
    return false;
    }

  this->DatabaseProxy->Open();
  midasResourceRecord record =
    this->DatabaseProxy->GetRecordByUuid(bitstream->GetUuid());


  if(record.Path != "" &&
     kwsys::SystemTools::FileExists(record.Path.c_str(), true))
    {

    this->DatabaseProxy->Close();
    return true;
    }

  std::stringstream fields;
  fields << "midas.bitstream.download?id=" << this->GetResourceHandle();

  if(this->Progress)
    {
    mws::WebAPI::Instance()->GetRestAPI()->SetProgressCallback(
      ProgressCallback, this->Progress);
    this->Progress->SetMessage(bitstream->GetName());
    this->Progress->ResetProgress();
    }
  std::stringstream status;
  status << "Downloading bitstream " << bitstream->GetName();
  this->Log->Status(status.str());

  mws::WebAPI::Instance()->DownloadFile(fields.str().c_str(),
                             bitstream->GetName().c_str());

  this->DatabaseProxy->AddResource(midasResourceType::BITSTREAM,
    bitstream->GetUuid(), WORKING_DIR() + "/" + bitstream->GetName(),
    bitstream->GetName(), midasResourceType::ITEM, parentId, 0);
  this->DatabaseProxy->Close();

  return true;
}
