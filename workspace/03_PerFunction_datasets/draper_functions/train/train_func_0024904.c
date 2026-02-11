Refine(vector<Reference<Shape> > &refined) const {
    for (int i = 0; i < ntris; ++i)
        refined.push_back(new Triangle(ObjectToWorld,
                          WorldToObject, ReverseOrientation,
                          (TriangleMesh *)this, i));
}
