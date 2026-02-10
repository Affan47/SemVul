CreateVertex(const R3Point& position, R3MeshVertex *v)
{

  if (!v) {
    v = new R3MeshVertex();
    v->flags.Add(R3_MESH_VERTEX_ALLOCATED);
  }


  SetVertexPosition(v, position);


  v->id = vertices.NEntries();


  vertices.Insert(v);


  return v;
}
