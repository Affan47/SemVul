ConvertRotationKeys(aiNodeAnim* na, const std::vector<const AnimationCurveNode*>& nodes,
		const LayerMap& layers,
		double& maxTime,
		double& minTime,
		Model::RotOrder order)
	{
		ai_assert(nodes.size());


		const std::vector< KeyFrameList >& inputs = GetKeyframeList(nodes);
		const KeyTimeList& keys = GetKeyTimeList(inputs);

		na->mNumRotationKeys = static_cast<unsigned int>(keys.size());
		na->mRotationKeys = new aiQuatKey[keys.size()];
		InterpolateKeys(na->mRotationKeys, keys, inputs, false, maxTime, minTime, order);
	}
