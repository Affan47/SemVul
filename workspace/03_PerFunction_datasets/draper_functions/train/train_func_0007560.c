Set(const CallMessage &call)
{
  MessageIter ri = call.reader();

  std::string iface_name;
  std::string property_name;
  Variant value;

  ri >> iface_name >> property_name >> value;

  InterfaceAdaptor *interface = (InterfaceAdaptor *) find_interface(iface_name);

  if (!interface)
    throw ErrorFailed("requested interface not found");

  on_set_property(*interface, property_name, value);

  interface->set_property(property_name, value);

  ReturnMessage reply(call);

  return reply;
}
