isDirectMotion(void) const
{
  if (myTransType ==  TRANS_NONE && myLastTransType == TRANS_NONE &&
      myRotType == ROT_NONE && myLastRotType == ROT_NONE &&
      (!hasLatVel() ||
       (hasLatVel() && myLatType == LAT_NONE && myLastLatType == LAT_NONE)))
    return false;
  else
    return true;
}
