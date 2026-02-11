PrintRequestedDocumentation(std::ostream& os)
{
  bool result = true;


  for(std::vector<RequestedHelpItem>::const_iterator
      i = this->RequestedHelpItems.begin();
      i != this->RequestedHelpItems.end();
      ++i)
    {
    this->SetForm(i->HelpForm);
    this->CurrentArgument = i->Argument;


    std::ofstream* fout = 0;
    std::ostream* s = &os;
    std::string docname("");
    if(i->Filename.length() > 0)
      {
      fout = new std::ofstream(i->Filename.c_str(), std::ios::out);
      if(fout)
        {
        s = fout;
        }
      else
        {
        result = false;
        }
      if(i->Filename != "-")
        {
        docname = cmSystemTools::GetFilenameWithoutLastExtension(i->Filename);
        }
      }


    if(!this->PrintDocumentation(i->HelpType, *s, docname.c_str()) || !*s)
      {
      result = false;
      }


    if(fout)
      {
      delete fout;
      }
    }
  return result;
}
