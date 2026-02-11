FinishRevision()
    {
    if(!this->Rev.Rev.empty())
      {

      this->CVS->Log << "Found revision " << this->Rev.Rev << "\n"
                     << "  author = " << this->Rev.Author << "\n"
                     << "  date = " << this->Rev.Date << "\n";
      this->Revisions.push_back(this->Rev);


      if(this->Revisions.size() >= 2)
        {
        this->Section = SectionEnd;
        }
      }
    this->Rev = Revision();
    }
