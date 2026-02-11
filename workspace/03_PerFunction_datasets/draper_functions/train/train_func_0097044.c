removeCamera(const char *cameraName)
{
  if (cameraName == NULL) {
    return false;
  }
  lock();

  std::map<std::string, CameraInfo*>::iterator iter =
                                            myCameraToInfoMap.find(cameraName);
  if (iter == myCameraToInfoMap.end()) {
    unlock();
    return false;
  }

  delete iter->second;
  iter->second = NULL;

  myCameraToInfoMap.erase(iter);

  setModified();

  unlock();

  return true;

}
