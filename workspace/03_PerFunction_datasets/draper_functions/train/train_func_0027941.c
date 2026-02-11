GetSourceFileWithOutput(const char *cname)
{
  std::string name = cname;
  std::string out;


  for(std::vector<cmSourceFile*>::const_iterator i =
        this->SourceFiles.begin(); i != this->SourceFiles.end(); ++i)
    {

    if ((*i)->GetCustomCommand())
      {

      const std::vector<std::string>& outputs =
        (*i)->GetCustomCommand()->GetOutputs();
      for(std::vector<std::string>::const_iterator o = outputs.begin();
          o != outputs.end(); ++o)
        {
        out = *o;
        std::string::size_type pos = out.rfind(name);

        if (pos != out.npos &&
            pos == out.size() - name.size() &&
            (pos ==0 || out[pos-1] == '/'))
          {
          return *i;
          }
        }
      }
    }


  return 0;
}
