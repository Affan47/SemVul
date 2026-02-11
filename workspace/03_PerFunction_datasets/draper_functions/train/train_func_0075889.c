SetSection(const char *name,
                                 cmDocumentationSection *section)
{
  if (this->AllSections.find(name) != this->AllSections.end())
    {
    delete this->AllSections[name];
    }
  this->AllSections[name] = section;
}
