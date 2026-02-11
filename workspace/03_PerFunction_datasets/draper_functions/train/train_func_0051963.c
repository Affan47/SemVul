Set(unsigned int index, AttributeValue* av) {
  if (Number()<=index) {
    ALIterator it;
    Last(it);
    int padding = index-Number();
    for (int i=0; i<padding; i++) Append(new AttributeValue());
    Append(av);
    return nil;
  }
  else {
    ALIterator it;
    First(it);
    for (int i=0; i<index; i++) Next(it);
    AttributeValue* oldv = Replace(it, av);
    return oldv;
  }
}
