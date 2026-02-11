StartElement(const char* name, const char** atts)
    {
    this->CurrentValue.clear();
    if(strcmp(name, "cdash") == 0)
      {
      this->CDashVersion = this->FindAttribute(atts, "version");
      }
    }
