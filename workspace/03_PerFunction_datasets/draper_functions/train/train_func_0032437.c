addCamera(const char *cameraName,
											                      const char *cameraType,
											                      const char *displayName,
											                      const char *displayType)
{
  if (cameraName == NULL) {
    return false;
  }

  lock();
  CameraInfo *info = findCameraInfo(cameraName);
  if (info != NULL) {
    unlock();
    return false;
  }

  info = new CameraInfo();

  info->myCameraName = cameraName;
  info->myCameraType = cameraType;
  info->myDisplayName = ((displayName != NULL) ? displayName : cameraName);
  info->myDisplayType = ((displayType != NULL) ? displayType : cameraType);

  myCameraToInfoMap[cameraName] = info;

  unlock();
  return true;

}
