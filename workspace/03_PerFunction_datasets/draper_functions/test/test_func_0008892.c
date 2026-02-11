execute()
{
  TinyVector<3> a;
  TinyVector<3> b;
  TinyVector<3,int> n;
  (*__corner1).execute();
  (*__corner2).execute();
  (*__meshSize).execute();
  for (size_t i=0; i<3; ++i) {
    a[i] = (*__corner1).value(i);
    b[i] = (*__corner2).value(i);
    n[i] = static_cast<int>((*__meshSize).value(i));
  }
  ffout(2) << "Building Mesh ... ";
  Structured3DMeshShape S(n[0], n[1], n[2], a, b);
  __mesh
    = new Structured3DMesh(S,
			   new VerticesCorrespondance(S.numberOfVertices()));
  ffout(2) << "done\n";
}
