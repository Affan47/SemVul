operator() (const std::string& name) 		const
{
  std::string result;
  const_form_iterator iter = getElement(name);
  if(iter != fFormData.end() && false == iter->isEmpty())
    result = iter->getValue();
  return result;
}
