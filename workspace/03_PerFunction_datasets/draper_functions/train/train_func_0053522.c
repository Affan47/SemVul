GetState(void)
{

  if ((mLogicalProb->GetState() == eNotMe) && (mVisualProb->GetState() == eNotMe))
    return eNotMe;
  return eDetecting;
}
