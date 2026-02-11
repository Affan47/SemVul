Copy (aiMaterial** _dest, const aiMaterial* src)
{
	ai_assert(NULL != _dest && NULL != src);

	aiMaterial* dest = (aiMaterial*) ( *_dest = new aiMaterial() );

	dest->Clear();
	delete[] dest->mProperties;

	dest->mNumAllocated  =  src->mNumAllocated;
	dest->mNumProperties =  src->mNumProperties;
	dest->mProperties    =  new aiMaterialProperty* [dest->mNumAllocated];

	for (unsigned int i = 0; i < dest->mNumProperties;++i)
	{
		aiMaterialProperty* prop  = dest->mProperties[i] = new aiMaterialProperty();
		aiMaterialProperty* sprop = src->mProperties[i];

		prop->mDataLength = sprop->mDataLength;
		prop->mData = new char[prop->mDataLength];
		::memcpy(prop->mData,sprop->mData,prop->mDataLength);

		prop->mIndex    = sprop->mIndex;
		prop->mSemantic = sprop->mSemantic;
		prop->mKey      = sprop->mKey;
		prop->mType		= sprop->mType;
	}
}
