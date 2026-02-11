constructMesh(SMesh* mesh)
{
	for (s32 i=0; i<Header.SubsetCount; ++i)
	{
		scene::SMeshBufferLightMap* meshBuffer = new scene::SMeshBufferLightMap();


		meshBuffer->Material.MaterialType = video::EMT_LIGHTMAP;
		meshBuffer->Material.Wireframe = false;
		meshBuffer->Material.Lighting = false;

		mesh->addMeshBuffer(meshBuffer);

		const u32 offs = Subsets[i].Offset * 3;

		for (u32 sc=0; sc<Subsets[i].Count; sc++)
		{
			const u32 idx = meshBuffer->getVertexCount();

			for (u32 vu=0; vu<3; ++vu)
			{
				const SLMTSTriangleDataEntry& v = Triangles[offs+(3*sc)+vu];
				meshBuffer->Vertices.push_back(
						video::S3DVertex2TCoords(
							v.X, v.Y, v.Z,
							video::SColor(255,255,255,255),
							v.U1, v.V1, v.U2, v.V2));
			}
			const core::vector3df normal = core::plane3df(
				meshBuffer->Vertices[idx].Pos,
				meshBuffer->Vertices[idx+1].Pos,
				meshBuffer->Vertices[idx+2].Pos).Normal;

			meshBuffer->Vertices[idx].Normal = normal;
			meshBuffer->Vertices[idx+1].Normal = normal;
			meshBuffer->Vertices[idx+2].Normal = normal;

			meshBuffer->Indices.push_back(idx);
			meshBuffer->Indices.push_back(idx+1);
			meshBuffer->Indices.push_back(idx+2);
		}
		meshBuffer->drop();
	}

	for (u32 j=0; j<mesh->MeshBuffers.size(); ++j)
		mesh->MeshBuffers[j]->recalculateBoundingBox();

	mesh->recalculateBoundingBox();
}
