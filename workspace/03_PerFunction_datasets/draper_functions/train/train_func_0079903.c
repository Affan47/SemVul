driverMess(int dev)
{
  if(dev>=m_videoHandles.size()){
    error("driverID (%d) must not exceed %d", dev, m_videoHandles.size());
    return;
  }
  if(dev>=0) {
    if(m_videoHandle){
      m_videoHandle->stop();
      m_videoHandle->close();
    }
    m_videoHandle=m_videoHandles[dev];
    if(m_videoHandle){
      if(m_videoHandle->open(m_writeprops)) {
        enumPropertyMess();
        if(STARTED==m_running)
	  m_videoHandle->start();
      }
    }
  } else {
    post("automatic driver selection");
  }
  m_driver=dev;
}
