add_device (const std::string & source, const std::string & device_name, unsigned capabilities, HalManager* )
{
  PTRACE(4, "VidInputCore\tAdding Device " << device_name);
  PWaitAndSignal m(core_mutex);

  VideoInputDevice device;
  for (std::set<VideoInputManager *>::iterator iter = managers.begin ();
       iter != managers.end ();
       iter++) {
    if ((*iter)->has_device (source, device_name, capabilities, device)) {

      if ( desired_device == device ) {
        internal_set_device(device, current_channel, current_format);
        boost::shared_ptr<Ekiga::Notification> notif (new Ekiga::Notification (Ekiga::Notification::Info, _("New device detected"), device.GetString ()));
        notification_core->push_notification (notif);
      }
      else {

        boost::shared_ptr<Ekiga::Notification> notif (new Ekiga::Notification (Ekiga::Notification::Info, _("New device detected"), device.GetString (), _("Use it"), boost::bind (&VideoInputCore::on_set_device, (VideoInputCore*) this, device)));
        notification_core->push_notification (notif);
      }

      device_added(device, desired_device == device);
    }
  }
}
