createMeshWithTangents(IMesh* mesh, bool recalculateNormals, bool smooth, bool angleWeighted, bool calculateTangents) const
{
	if (!mesh)
		return 0;


	SMesh* clone = new SMesh();
	const u32 meshBufferCount = mesh->getMeshBufferCount();

	for (u32 b=0; b<meshBufferCount; ++b)
	{
		const IMeshBuffer* original = mesh->getMeshBuffer(b);
		const u32 idxCnt = original->getIndexCount();
		const u16* idx = original->getIndices();

		SMeshBufferTangents* buffer = new SMeshBufferTangents();

		buffer->Material = original->getMaterial();
		buffer->Vertices.reallocate(idxCnt);
		buffer->Indices.set_used(idxCnt);

		core::map<video::S3DVertexTangents, int> vertMap;
		int vertLocation;


		const video::E_VERTEX_TYPE vType = original->getVertexType();
		video::S3DVertexTangents vNew;
		for (u32 i=0; i<idxCnt; ++i)
		{
			switch(vType)
			{
			case video::EVT_STANDARD:
				{
					const video::S3DVertex* v =
						(const video::S3DVertex*)original->getVertices();
					vNew = video::S3DVertexTangents(
							v[idx[i]].Pos, v[idx[i]].Normal, v[idx[i]].Color, v[idx[i]].TCoords);
				}
				break;
			case video::EVT_2TCOORDS:
				{
					const video::S3DVertex2TCoords* v =
						(const video::S3DVertex2TCoords*)original->getVertices();
					vNew = video::S3DVertexTangents(
							v[idx[i]].Pos, v[idx[i]].Normal, v[idx[i]].Color, v[idx[i]].TCoords);
				}
				break;
			case video::EVT_TANGENTS:
				{
					const video::S3DVertexTangents* v =
						(const video::S3DVertexTangents*)original->getVertices();
					vNew = v[idx[i]];
				}
				break;
			}
			core::map<video::S3DVertexTangents, int>::Node* n = vertMap.find(vNew);
			if (n)
			{
				vertLocation = n->getValue();
			}
			else
			{
				vertLocation = buffer->Vertices.size();
				buffer->Vertices.push_back(vNew);
				vertMap.insert(vNew, vertLocation);
			}


			buffer->Indices[i] = vertLocation;
		}
		buffer->recalculateBoundingBox();


		clone->addMeshBuffer(buffer);
		buffer->drop();
	}

	clone->recalculateBoundingBox();
	if (calculateTangents)
		recalculateTangents(clone, recalculateNormals, smooth, angleWeighted);

	return clone;
}
