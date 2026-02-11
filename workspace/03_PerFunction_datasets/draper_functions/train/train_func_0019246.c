PrintClasses()
{
  if ( this->ClassStack.size() == 0 )
    {
    std::cerr << "Error when parsing. No classes on class stack" << std::endl;
    abort();
    }
  std::vector<cmStdString> files = this->GetFilesProduced();
  std::vector<cmStdString>::iterator sit;
  for ( sit = files.begin();
    sit != files.end();
    ++ sit )
    {
    std::cout << "  " << sit->c_str() << ".class" << std::endl;
    }
}
