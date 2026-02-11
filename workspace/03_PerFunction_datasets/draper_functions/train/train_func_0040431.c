FindImplicitConflicts(cmOStringStream& w)
    {
    bool first = true;
    for(unsigned int i=0; i < this->OD->OriginalDirectories.size(); ++i)
      {

      std::string const& dir = this->OD->OriginalDirectories[i];
      if(dir != this->Directory && this->FindConflict(dir))
        {


        if(first)
          {
          first = false;
          w << "  ";
          this->Report(w);
          w << " in " << this->Directory << " may be hidden by files in:\n";
          }
        w << "    " << dir << "\n";
        }
      }
    }
