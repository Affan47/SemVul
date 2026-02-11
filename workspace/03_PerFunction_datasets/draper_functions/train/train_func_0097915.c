CheckIndices(D3DS::Mesh& sMesh)
{
	for (std::vector< D3DS::Face >::iterator i =  sMesh.mFaces.begin(); i != sMesh.mFaces.end();++i)
	{

		for (unsigned int a = 0; a < 3;++a)
		{
			if ((*i).mIndices[a] >= sMesh.mPositions.size())
			{
				DefaultLogger::get()->warn("3DS: Vertex index overflow)");
				(*i).mIndices[a] = (uint32_t)sMesh.mPositions.size()-1;
			}
			if ( !sMesh.mTexCoords.empty() && (*i).mIndices[a] >= sMesh.mTexCoords.size())
			{
				DefaultLogger::get()->warn("3DS: Texture coordinate index overflow)");
				(*i).mIndices[a] = (uint32_t)sMesh.mTexCoords.size()-1;
			}
		}
	}
}
