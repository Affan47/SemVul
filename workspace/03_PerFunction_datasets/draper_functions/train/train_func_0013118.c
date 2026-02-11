setup_conf_bridge ()
{
  PWaitAndSignal m(core_mutex);

  videoinput_core_conf_bridge = new VideoInputCoreConfBridge (*this);
}
