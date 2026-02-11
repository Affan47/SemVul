SetForm(Form f, int manSection)
{
  switch(f)
  {
    case HTMLForm:
      this->CurrentFormatter = &this->HTMLFormatter;
      break;
    case DocbookForm:
      this->CurrentFormatter = &this->DocbookFormatter;
      break;
    case ManForm:
      this->ManFormatter.SetManSection(manSection);
      this->CurrentFormatter = &this->ManFormatter;
      break;
    case TextForm:
      this->CurrentFormatter = &this->TextFormatter;
      break;
    case UsageForm:
      this->CurrentFormatter = & this->UsageFormatter;
      break;
  }
}
