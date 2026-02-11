reallocateBuffers()
{
	if (Particles.size() * 4 > Buffer->getVertexCount() ||
			Particles.size() * 6 > Buffer->getIndexCount())
	{
		u32 oldSize = Buffer->getVertexCount();
		Buffer->Vertices.set_used(Particles.size() * 4);

		u32 i;


		for (i=oldSize; i<Buffer->Vertices.size(); i+=4)
		{
			Buffer->Vertices[0+i].TCoords.set(0.0f, 0.0f);
			Buffer->Vertices[1+i].TCoords.set(0.0f, 1.0f);
			Buffer->Vertices[2+i].TCoords.set(1.0f, 1.0f);
			Buffer->Vertices[3+i].TCoords.set(1.0f, 0.0f);
		}


		u32 oldIdxSize = Buffer->getIndexCount();
		u32 oldvertices = oldSize;
		Buffer->Indices.set_used(Particles.size() * 6);

		for (i=oldIdxSize; i<Buffer->Indices.size(); i+=6)
		{
			Buffer->Indices[0+i] = (u16)0+oldvertices;
			Buffer->Indices[1+i] = (u16)2+oldvertices;
			Buffer->Indices[2+i] = (u16)1+oldvertices;
			Buffer->Indices[3+i] = (u16)0+oldvertices;
			Buffer->Indices[4+i] = (u16)3+oldvertices;
			Buffer->Indices[5+i] = (u16)2+oldvertices;
			oldvertices += 4;
		}
	}
}
