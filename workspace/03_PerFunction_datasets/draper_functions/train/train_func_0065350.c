stop()
{
  if (!isGood())
    return(NOT_INITED);

  if (!comArmStop())
    return(COMM_FAILED);

  return(SUCCESS);
}
