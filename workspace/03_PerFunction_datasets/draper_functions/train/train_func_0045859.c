aiGetMaterialIntegerArray(const aiMaterial* pMat,
	const char* pKey,
	unsigned int type,
    unsigned int index,
	int* pOut,
	unsigned int* pMax)
{
	ai_assert (pOut != NULL);
	ai_assert (pMat != NULL);

	const aiMaterialProperty* prop;
	aiGetMaterialProperty(pMat,pKey,type,index,(const aiMaterialProperty**) &prop);
	if (!prop) {
		return AI_FAILURE;
	}


	unsigned int iWrite = 0;
	if( aiPTI_Integer == prop->mType || aiPTI_Buffer == prop->mType)	{
		iWrite = prop->mDataLength / sizeof(int32_t);
		if (pMax) {
			iWrite = std::min(*pMax,iWrite); ;
		}
		for (unsigned int a = 0; a < iWrite;++a) {
			pOut[a] = static_cast<int>(reinterpret_cast<int32_t*>(prop->mData)[a]);
		}
		if (pMax) {
			*pMax = iWrite;
		}
	}

	else if( aiPTI_Float == prop->mType)	{
		iWrite = prop->mDataLength / sizeof(float);
		if (pMax) {
			iWrite = std::min(*pMax,iWrite); ;
		}
		for (unsigned int a = 0; a < iWrite;++a) {
			pOut[a] = static_cast<int>(reinterpret_cast<float*>(prop->mData)[a]);
		}
		if (pMax) {
			*pMax = iWrite;
		}
	}

	else	{
		if (pMax) {
			iWrite = *pMax;
		}

		const char* cur =  prop->mData+4;
		ai_assert(prop->mDataLength>=5 && !prop->mData[prop->mDataLength-1]);
		for (unsigned int a = 0; ;++a) {
			pOut[a] = strtol10(cur,&cur);
			if(a==iWrite-1) {
				break;
			}
			if(!IsSpace(*cur)) {
				DefaultLogger::get()->error("Material property" + std::string(pKey) +
					" is a string; failed to parse an integer array out of it.");
				return AI_FAILURE;
			}
		}

		if (pMax) {
			*pMax = iWrite;
		}
	}
	return AI_SUCCESS;
}
