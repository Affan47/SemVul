addWeight(SJoint *joint)
{
	if (!joint)
		return 0;

	joint->Weights.push_back(SWeight());
	return &joint->Weights.getLast();
}
