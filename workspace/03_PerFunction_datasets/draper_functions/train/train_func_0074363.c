SetCurrentAnimationClip(FCDAnimationClip* clip)
{
	if (currentClip == clip) return;

	currentClip = NULL;
	float clipOffset = 0.0f;
	for (size_t i = 0; i < clips.size(); ++i)
	{
		if (clips[i] == clip)
		{
			currentClip = clips[i];
			clipOffset = clipOffsets[i];
			break;
		}
	}

	if (currentClip != NULL)
	{
		float offset = clipOffset - currentOffset;
		currentOffset = clipOffset;
		for (FCDAnimationKeyList::iterator it = keys.begin(); it != keys.end(); ++it)
		{
			(*it)->input += offset;
		}
	}

	SetDirtyFlag();
}
