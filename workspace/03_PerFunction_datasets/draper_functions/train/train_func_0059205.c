AddNodePrefixes(aiNode* node, const char* prefix, unsigned int len)
{
	ai_assert(NULL != prefix);
	PrefixString(node->mName,prefix,len);


	for (unsigned int i = 0; i < node->mNumChildren;++i)
		AddNodePrefixes(node->mChildren[i],prefix,len);
}
