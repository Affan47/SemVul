setViewport(SbVec2f origin, SbVec2f size)
{
#if COIN_DEBUG
  if (size[0]<0) {
    SoDebugError::postWarning("SbViewportRegion::setViewport",
                              "size[0] (%d) should be >=0. Clamped to 0.",
                              size[0]);
    size[0]=0;
  }
  if (size[1]<0) {
    SoDebugError::postWarning("SbViewportRegion::setViewport",
                              "size[1] (%d) should be >=0. Clamped to 0.",
                              size[1]);
    size[1]=0;
  }
#endif

  this->setViewport(origin[0], origin[1], size[0], size[1]);
}
