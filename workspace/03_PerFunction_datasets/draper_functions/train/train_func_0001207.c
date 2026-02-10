CheckArgumentValue(std::string const& arg)
{

  if(this->ArgumentDoing == ArgumentDoingLabels)
    {
    this->Labels.insert(arg);
    return true;
    }


  return this->Superclass::CheckArgumentValue(arg);
}
