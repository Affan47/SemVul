home(int joint)
{
  if (!isGood())
    return(NOT_INITED);

  if ((joint < 0) && !comArmHome(0xff))
    return(COMM_FAILED);
  else if ((joint > 0) && (joint <= NumJoints) && !comArmHome(joint))
    return(COMM_FAILED);
  else
    return(INVALID_JOINT);

  return(SUCCESS);
}
