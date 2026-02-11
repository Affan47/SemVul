operator()(const TinyVector<3, real_t>& X) const
{
  for (std::list<ConstReferenceCounting<Object> >::const_iterator i = __objects.begin();
       i != __objects.end(); ++i) {
    if ((*i)->inside(X)) {
      return 1;
    }
  }
  return 0;
}
