AddJoint(FCDSceneNode* j)
{
	if (j != NULL)
	{
		j->SetJointFlag(true);
		AppendJoint(j);
		return true;
	}
	return false;
}
