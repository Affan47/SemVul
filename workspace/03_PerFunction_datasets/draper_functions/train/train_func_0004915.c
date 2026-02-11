GetTextureIndex(const std::string& filename)
{
	unsigned int iIndex = 0;
	for (std::vector<std::string>::const_iterator
		i =  aszTextures.begin();
		i != aszTextures.end();++i,++iIndex)
	{

		if (0 == ASSIMP_stricmp ( filename.c_str(),(*i).c_str()))return iIndex;
	}
	iIndex = (unsigned int)aszTextures.size();
	aszTextures.push_back(filename);
	return iIndex;
}
