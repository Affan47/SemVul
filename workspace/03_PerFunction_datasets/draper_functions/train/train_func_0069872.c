ApplyMasterScale(aiScene* pScene)
{

	if (!mMasterScale)mMasterScale = 1.0f;
	else mMasterScale = 1.0f / mMasterScale;


	pScene->mRootNode->mTransformation *= aiMatrix4x4(
		mMasterScale,0.0f, 0.0f, 0.0f,
		0.0f, mMasterScale,0.0f, 0.0f,
		0.0f, 0.0f, mMasterScale,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);


}
