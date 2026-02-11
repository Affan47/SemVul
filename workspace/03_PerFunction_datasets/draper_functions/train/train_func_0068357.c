putState(bool new_state)
{
  if(new_state != bDrivingState) {
    bDrivingState = new_state;
    Vth = bDrivingState ? 5.0 : 0.3;

    if(verbose & 1)
      cout << name()<< " putState= "
	   << (new_state ? "high" : "low") << endl;


    if(snode)
      snode->update();
  }
  if(m_monitor)
    m_monitor->putState(new_state?'1':'0');

}
