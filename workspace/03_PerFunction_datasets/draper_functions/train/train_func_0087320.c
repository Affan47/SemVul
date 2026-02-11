AppendSection(const char *name,
                                    cmDocumentationEntry &docs)
{

  std::vector<cmDocumentationEntry> docsVec;
  docsVec.push_back(docs);
  this->AppendSection(name,docsVec);
}
