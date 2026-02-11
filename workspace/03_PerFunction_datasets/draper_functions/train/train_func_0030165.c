addCameraCommand(const char *cameraName,
												                           const char *command,
												                           const char *cameraCommandName,
                                                   int requestInterval)
{
  if (command == NULL) {
    return false;
  }
  lock();

  CameraInfo *cameraInfo = findCameraInfo(cameraName);
  if (cameraInfo == NULL) {
    unlock();
    return false;
  }

  CommandInfo *info = findCommandInfo(cameraName, command);
  if (info != NULL) {
    unlock();
    return false;
  }

  info = new CommandInfo();
  info->myCommand = command;
  info->myCameraCommandName = cameraCommandName;
  info->myRequestInterval = requestInterval;


  cameraInfo->myCommandToInfoMap[command] = info;

  setModified();
  unlock();

  return true;

}
