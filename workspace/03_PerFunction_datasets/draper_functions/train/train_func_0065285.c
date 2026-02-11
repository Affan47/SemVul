ProcessAnimationChannel (aiNodeAnim* anim)
{
	int i = 0;


	ai_assert((0 != anim->mPositionKeys && 0 != anim->mRotationKeys && 0 != anim->mScalingKeys));


	if (anim->mNumPositionKeys > 1 && AllIdentical(anim->mPositionKeys,anim->mNumPositionKeys,configEpsilon))
	{
		aiVectorKey v = anim->mPositionKeys[0];


		delete[] anim->mPositionKeys;
		anim->mPositionKeys = new aiVectorKey[anim->mNumPositionKeys = 1];
		anim->mPositionKeys[0] = v;
		i = 1;
	}


	if (anim->mNumRotationKeys > 1 && AllIdentical(anim->mRotationKeys,anim->mNumRotationKeys,configEpsilon))
	{
		aiQuatKey v = anim->mRotationKeys[0];


		delete[] anim->mRotationKeys;
		anim->mRotationKeys = new aiQuatKey[anim->mNumRotationKeys = 1];
		anim->mRotationKeys[0] = v;
		i = 1;
	}


	if (anim->mNumScalingKeys > 1 && AllIdentical(anim->mScalingKeys,anim->mNumScalingKeys,configEpsilon))
	{
		aiVectorKey v = anim->mScalingKeys[0];


		delete[] anim->mScalingKeys;
		anim->mScalingKeys = new aiVectorKey[anim->mNumScalingKeys = 1];
		anim->mScalingKeys[0] = v;
		i = 1;
	}
	if (1 == i)
		DefaultLogger::get()->warn("Simplified dummy tracks with just one key");
}
