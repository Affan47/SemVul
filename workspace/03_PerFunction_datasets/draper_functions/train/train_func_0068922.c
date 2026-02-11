CSceneNodeAnimatorTexture(const core::array<video::ITexture*>& textures,
					 s32 timePerFrame, bool loop, u32 now)
: ISceneNodeAnimatorFinishing(0),
	TimePerFrame(timePerFrame), StartTime(now), Loop(loop)
{
	#ifdef _DEBUG
	setDebugName("CSceneNodeAnimatorTexture");
	#endif

	for (u32 i=0; i<textures.size(); ++i)
	{
		if (textures[i])
			textures[i]->grab();

		Textures.push_back(textures[i]);
	}

	FinishTime = now + (timePerFrame * Textures.size());
}
