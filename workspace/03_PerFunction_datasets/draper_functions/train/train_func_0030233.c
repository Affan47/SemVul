AddDocumentIntroToPrint(const char* intro[2])
{
  const char* docname = this->GetDocName(false);
  if(intro && docname)
    {
    cmDocumentationSection* section;
    std::string desc("");

    desc += docname;
    desc += " - ";
    desc += intro[1];

    section = new cmDocumentationSection("Introduction", "NAME");
    section->Append(0, desc.c_str(), 0);
    this->PrintSections.push_back(section);
    }
}
