visitGroup(const Group *obj)
{
  for (Group::const_iterator it = obj->begin(); it != obj->end(); ++it)
    (*it)->accept(*this);
}
