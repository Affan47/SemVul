fixCommutedOpIndices(unsigned &ResultIdx1,
                                           unsigned &ResultIdx2,
                                           unsigned CommutableOpIdx1,
                                           unsigned CommutableOpIdx2) {
  if (ResultIdx1 == CommuteAnyOperandIndex &&
      ResultIdx2 == CommuteAnyOperandIndex) {
    ResultIdx1 = CommutableOpIdx1;
    ResultIdx2 = CommutableOpIdx2;
  } else if (ResultIdx1 == CommuteAnyOperandIndex) {
    if (ResultIdx2 == CommutableOpIdx1)
      ResultIdx1 = CommutableOpIdx2;
    else if (ResultIdx2 == CommutableOpIdx2)
      ResultIdx1 = CommutableOpIdx1;
    else
      return false;
  } else if (ResultIdx2 == CommuteAnyOperandIndex) {
    if (ResultIdx1 == CommutableOpIdx1)
      ResultIdx2 = CommutableOpIdx2;
    else if (ResultIdx1 == CommutableOpIdx2)
      ResultIdx2 = CommutableOpIdx1;
    else
      return false;
  } else


    return (ResultIdx1 == CommutableOpIdx1 && ResultIdx2 == CommutableOpIdx2) ||
           (ResultIdx1 == CommutableOpIdx2 && ResultIdx2 == CommutableOpIdx1);

  return true;
}
