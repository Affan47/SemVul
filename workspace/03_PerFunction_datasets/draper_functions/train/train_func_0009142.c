getPose(void) const
{
  ArPose pose;
  if (myPosePointer != NULL)
    return *myPosePointer;
  else
    return pose;
}
