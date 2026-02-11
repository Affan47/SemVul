removeEmptyBoundaries()
{
  BodyElement** bels = new BodyElement*[modelStatistics->nofElements];

  int counter = 0;

  int index = 0;
  while (true) {
    BodyElement* be = getBoundary(index++);
    if (be==NULL) break;
    if ( 0 == be->getNofMeshElements() ) {
      bels[counter++] = be;
    }
  }

  for (int i = 0; i < counter; i++) {
    removeBodyElement(bels[i], true);
  }
}
