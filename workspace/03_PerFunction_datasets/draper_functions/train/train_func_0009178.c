CountTracks(D3DS::Node* node, unsigned int& cnt)
{


	if (node->aPositionKeys.size()  > 1  || node->aRotationKeys.size()   > 1   ||
		node->aScalingKeys.size()   > 1  || node->aCameraRollKeys.size() > 1 ||
		node->aTargetPositionKeys.size()  > 1)
	{
		++cnt;


		if (node->aTargetPositionKeys.size()  > 1)++cnt;
	}


	for (unsigned int i = 0; i < node->mChildren.size();++i)
		CountTracks(node->mChildren[i],cnt);
}
