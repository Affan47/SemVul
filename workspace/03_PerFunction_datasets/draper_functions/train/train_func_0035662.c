getPose(unsigned int ind, CPose2D &outPose)
{
	if (ind>=poses.size()) THROW_EXCEPTION("Index out of range!!");

	outPose = poses[ind];
}
