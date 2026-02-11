Update(void)
{

    bbox = R3null_box;
    for (int i = 0; i < vertices.NEntries(); i++) {
      R3TriangleVertex *v = vertices.Kth(i);
      bbox.Union(v->Position());
    }
}
