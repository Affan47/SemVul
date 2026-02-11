DoRevision(Revision const& revision,
                                 std::vector<Change> const& changes)
{

  if(revision.Rev == this->OldRevision)
    {
    this->PriorRev = revision;
    return;
    }


  cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);


  this->Revisions.push_back(revision);


  Revision const& rev = this->Revisions.back();
  this->Log << "Found revision " << rev.Rev << "\n"
            << "  author = " << rev.Author << "\n"
            << "  date = " << rev.Date << "\n";


  for(std::vector<Change>::const_iterator ci = changes.begin();
      ci != changes.end(); ++ci)
    {
    if(const char* local = this->LocalPath(ci->Path))
      {
      std::string dir = cmSystemTools::GetFilenamePath(local);
      std::string name = cmSystemTools::GetFilenameName(local);
      File& file = this->Dirs[dir][name];
      file.PriorRev = file.Rev? file.Rev : &this->PriorRev;
      file.Rev = &rev;
      this->Log << "  " << ci->Action << " " << local << " " << "\n";
      }
    }
}
