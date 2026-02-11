HasNameMatch(const aiString& in, aiNode* node)
{
	int result = (node->mName == in ? 1 : 0 );
	for (unsigned int i = 0; i < node->mNumChildren;++i)	{
		result += HasNameMatch(in,node->mChildren[i]);
	}
	return result;
}
