MeshEntryToVertexFormat(std::vector<VERTEX_FORMAT>& list,
                                         const RenderMesh* mesh,
                                         size_t startIndex,
                                         bool bClipMesh) {
  bool bHasNormal = mesh->GetNormalIndices().size() == mesh->GetVertexIndices().size();

  VERTEX_FORMAT f;


  for (size_t i = 0;i<3;i++) {
    size_t vertexIndex =  mesh->GetVertexIndices()[startIndex+i];
    f.m_vPos =  mesh->GetVertices()[vertexIndex];

    if (mesh->UseDefaultColor()) {
      f.m_vVertexData = mesh->GetDefaultColor().xyz();
      f.m_fOpacity = mesh->GetDefaultColor().w;
    } else {
      f.m_vVertexData = mesh->GetColors()[vertexIndex].xyz();
      f.m_fOpacity = mesh->GetColors()[vertexIndex].w;
    }

    if (bHasNormal)
      f.m_vNormal = mesh->GetNormals()[vertexIndex];
    else
      f.m_vNormal = FLOATVECTOR3(2,2,2);

    f.m_bClip = bClipMesh;

    list.push_back(f);
  }
}
