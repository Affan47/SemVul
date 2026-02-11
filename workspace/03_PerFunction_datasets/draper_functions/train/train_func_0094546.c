internalOpen(void)
{
  havePose = false;
  myFD = ArUtil::fopen(myLogFile, "r");
  if (myFD == NULL)
    {
      myStatus = STATUS_OPEN_FAILED;
      return OPEN_FILE_NOT_FOUND;
    }

  char buf[100];
  if (fgets(buf,100,myFD) != NULL)
    {
      if (strncmp(buf, "// Saphira log file", 19) != 0)
        {
          myStatus = STATUS_OPEN_FAILED;
          fclose(myFD);
          myFD = NULL;
          return OPEN_NOT_A_LOG_FILE;
        }
    }
  else
    {
      myStatus = STATUS_OPEN_FAILED;
      fclose(myFD);
      myFD = NULL;
      return OPEN_NOT_A_LOG_FILE;
    }


  if (fgets(buf,100,myFD) != NULL)
    {
      if (strncmp(buf, "// Robot position", 17) == 0)
        {
          int x,y,th;
          fgets(buf,100,myFD);
          sscanf(buf, "%d %d %d", &x, &y, &th);
          myPose.setX(x);
          myPose.setY(y);
          myPose.setTh(th);
          havePose = true;
        }
      if (strncmp(buf, "// Robot name", 13) == 0)
        {
          fgets(buf,100,myFD);
          sscanf(buf, "%s %s %s", myName, myType, mySubtype);
        }
    }

  myStatus = STATUS_OPEN;
  return 0;
}
