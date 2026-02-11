waitForMoreNodes() const
{
  if (blockingAccess)
    return moreNodesCondition_.wait();
  else
    return 0;
}
