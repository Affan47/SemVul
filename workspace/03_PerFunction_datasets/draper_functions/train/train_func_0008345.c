GetFilesProduced()
{
  std::vector<cmStdString> files;
  CurrentClass* toplevel = &(*(this->ClassStack.begin()));
  std::vector<CurrentClass>::iterator it;
  for ( it = toplevel->NestedClasses->begin();
    it != toplevel->NestedClasses->end();
    ++ it )
    {
    it->AddFileNamesForPrinting(&files, 0, "$");
    }
  return files;
}
