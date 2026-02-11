afConvertDelta (deltaStr, deltaSize, newDeltaSize)
     char  *deltaStr;
     size_t deltaSize, *newDeltaSize;
{
  struct ed_cmd cmd;
  size_t idx;
  char *deltaPtr = deltaStr, *deltaEnd = deltaStr + deltaSize;
  char *newDelta, *newDeltaPtr;

  if (deltaSize < 16)
    deltaSize = 16;

  if ((newDelta = malloc ((unsigned) deltaSize*2)) == NULL)
    FAIL ("ConvertDelta", "malloc", AF_ESYSERR, NULL);
  newDeltaPtr = newDelta;


  while (deltaPtr < deltaEnd) {
    memcpy ((char *)&cmd, deltaPtr, sizeof (cmd));
    deltaPtr += sizeof (cmd);

    newDeltaPtr += putCmd (cmd.cmd, cmd.length, newDeltaPtr);

    switch (cmd.cmd) {
    case MV:
      memcpy ((char*)&idx, deltaPtr, sizeof (idx));
      deltaPtr += sizeof (idx);
      newDeltaPtr += putIndex (idx, newDeltaPtr);
      break;
    case AD:
      memcpy (newDeltaPtr, deltaPtr, (size_t) cmd.length);
      deltaPtr += cmd.length;
      newDeltaPtr += cmd.length;
      break;
    }
  }
  *newDeltaSize = newDeltaPtr - newDelta;
  return (newDelta);
}
