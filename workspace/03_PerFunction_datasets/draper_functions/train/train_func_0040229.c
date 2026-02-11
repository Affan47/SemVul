setFrame(int no, bool force)
{
  if (!force && no == mCurrentFrame) return;
  if (no<0 || no >=mFrames.count()) return;
  setPixmap(mFrames.at(no));

  QPoint offset = thememanager()->getOffset();


  resetTransform();
  if (mOffsetStatus)
  {
    translate(-mHotspots.at(no).x()+offset.x(), -mHotspots.at(no).y()+offset.y());
  }
  else
  {
    translate(-mHotspots.at(no).x(), -mHotspots.at(no).y());
  }
  mCurrentFrame = no;
  update();
}
