readSubMesh(io::IReadFile* file, ChunkData& parent, OgreSubMesh& subMesh)
{
#ifdef IRR_OGRE_LOADER_DEBUG
	os::Printer::log("Read Submesh");
#endif
	readString(file, parent, subMesh.Material);
#ifdef IRR_OGRE_LOADER_DEBUG
	os::Printer::log("using material", subMesh.Material);
#endif
	readBool(file, parent, subMesh.SharedVertices);

	s32 numIndices;
	readInt(file, parent, &numIndices);
	subMesh.Indices.set_used(numIndices);

	readBool(file, parent, subMesh.Indices32Bit);

	if (subMesh.Indices32Bit)
		readInt(file, parent, subMesh.Indices.pointer(), numIndices);
	else
	{
		for (s32 i=0; i<numIndices; ++i)
		{
			u16 num;
			readShort(file, parent, &num);
			subMesh.Indices[i]=num;
		}
	}

	while(parent.read < parent.header.length)
	{
		ChunkData data;
		readChunkData(file, data);

		switch(data.header.id)
		{
		case COGRE_GEOMETRY:
			readGeometry(file, data, subMesh.Geometry);
		break;
		case COGRE_SUBMESH_OPERATION:
			readShort(file, data, &subMesh.Operation);
#ifdef IRR_OGRE_LOADER_DEBUG
			os::Printer::log("Read Submesh Operation",core::stringc(subMesh.Operation));
#endif
			if (subMesh.Operation != 4)
				os::Printer::log("Primitive type != trilist not yet implemented", ELL_WARNING);
			break;
		case COGRE_SUBMESH_TEXTURE_ALIAS:
		{
#ifdef IRR_OGRE_LOADER_DEBUG
				os::Printer::log("Read Submesh Texture Alias");
#endif
			core::stringc texture, alias;
			readString(file, data, texture);
			readString(file, data, alias);
			subMesh.TextureAliases.push_back(OgreTextureAlias(texture,alias));
		}
			break;
		case COGRE_SUBMESH_BONE_ASSIGNMENT:
		{
			subMesh.BoneAssignments.push_back(OgreBoneAssignment());
			readInt(file, data, &subMesh.BoneAssignments.getLast().VertexID);
			readShort(file, data, &subMesh.BoneAssignments.getLast().BoneID);
			readFloat(file, data, &subMesh.BoneAssignments.getLast().Weight);
		}
			break;
		default:
#ifdef IRR_OGRE_LOADER_DEBUG
			os::Printer::log("Skipping", core::stringc(data.header.id));
#endif
			parent.read=parent.header.length;
			file->seek(-(long)sizeof(ChunkHeader), true);
			return true;
		}
		parent.read += data.read;
	}
	return true;
}
