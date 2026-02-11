Copy     (aiBone** _dest, const aiBone* src)
{
	ai_assert(NULL != _dest && NULL != src);

	aiBone* dest = *_dest = new aiBone();


	::memcpy(dest,src,sizeof(aiBone));


	GetArrayCopy( dest->mWeights, dest->mNumWeights );
}
