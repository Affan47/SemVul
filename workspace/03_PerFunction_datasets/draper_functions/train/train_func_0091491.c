loadParamFile(const char *file)
{
  if (myParams != NULL)
    delete myParams;

  myParams = new ArRobotGeneric("");
  if (!myParams->parseFile(file, false, true))
  {
    ArLog::log(ArLog::Normal, "ArRobot::loadParamFile: Could not find file '%s' to load.", file);
    return false;
  }
  processParamFile();
  ArLog::log(ArLog::Normal, "Loaded robot parameters from %s.", file);
  return true;
}
