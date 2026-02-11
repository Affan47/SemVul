current (void)
{
  void* temp = ACE_Service_Config::singleton()->threadkey_.get ();
  if (temp == 0) {


    temp = global();
    singleton()->threadkey_.set (temp);
  }

  return static_cast<ACE_Service_Gestalt*> (temp);
}
