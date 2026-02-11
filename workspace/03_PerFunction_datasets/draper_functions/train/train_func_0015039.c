GuessBase(std::vector<Change> const& changes)
{


  for(std::string::size_type slash = this->URL.find('/');
      this->Base.empty() && slash != std::string::npos;
      slash = this->URL.find('/', slash+1))
    {

    std::string base = cmCTest::DecodeURL(this->URL.substr(slash));
    for(std::vector<Change>::const_iterator ci = changes.begin();
        this->Base.empty() && ci != changes.end(); ++ci)
      {
      if(cmCTestSVNPathStarts(ci->Path, base))
        {
        this->Base = base;
        }
      }
    }


  this->Base += "/";

  this->Log << "Guessed Base = " << this->Base << "\n";
}
