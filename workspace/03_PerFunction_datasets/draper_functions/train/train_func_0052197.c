execute()
{
  BoundaryList* b = new BoundaryList();

  for(List::iterator i = __boundaries.begin();
      i != __boundaries.end(); ++i) {
    (**i).execute();
    b->add((**i).boundary());
  }
  __boundary = b;
}
