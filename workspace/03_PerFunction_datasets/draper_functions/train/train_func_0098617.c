__findVertex(const Vertex * const p) {
  for(Triangles::iterator i = __triangles.begin(); i != __triangles.end(); ++i) {
    for(unsigned j=0;j<3;++j)
      if (i->base()[j] == p)
	return &*i;
  }
  ASSERT(false);
  return NULL;
}
