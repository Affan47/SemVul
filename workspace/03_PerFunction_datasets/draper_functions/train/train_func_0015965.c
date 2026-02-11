isContinued (const String& value)
  {


    bool status = false;
    String::size_type ampTest = value.find_last_not_of(String(" \n\t'"));
    if (ampTest != String::npos)
    {
       if (value[ampTest] == '&')
       {
          status = true;
       }
    }

    return status;
  }
