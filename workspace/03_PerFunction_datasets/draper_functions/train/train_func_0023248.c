getToLocalTransform(void) const
{
  ArTransform trans;
  ArPose origin(0, 0, 0);
  ArPose pose = getPose();

  trans.setTransform(pose, origin);
  return trans;
}
