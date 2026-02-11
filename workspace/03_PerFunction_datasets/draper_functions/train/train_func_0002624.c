ProcessLine()
    {
    if(this->RegexUpdate.find(this->Line))
      {
      this->DoPath(this->RegexUpdate.match(1)[0],
                   this->RegexUpdate.match(2)[0],
                   this->RegexUpdate.match(3)[0],
                   this->RegexUpdate.match(4));
      }
    return true;
    }
