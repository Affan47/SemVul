SetPropertyMatrix(const char* szName, const aiMatrix4x4& value,
	bool* bWasExisting )
{
	ASSIMP_BEGIN_EXCEPTION_REGION();
	SetGenericProperty<aiMatrix4x4>(pimpl->mMatrixProperties, szName,value,bWasExisting);
	ASSIMP_END_EXCEPTION_REGION(void);
}
