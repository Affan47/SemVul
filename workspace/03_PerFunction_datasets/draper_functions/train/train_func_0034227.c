getVariable(const std::string& name)throw(NutException)
{
  if(getClient()->hasDeviceVariable(getName(), name))
  	return Variable(this, name);
  else
    return Variable(NULL, "");
}
