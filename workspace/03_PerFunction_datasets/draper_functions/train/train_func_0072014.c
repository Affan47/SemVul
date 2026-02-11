removeMethod(XmlRpcServerMethod* method)
{
  MethodMap::iterator i = _methods.find(method->name());
  if (i != _methods.end())
    _methods.erase(i);
}
