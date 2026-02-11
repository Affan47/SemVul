notify_has_actions (EkigaCallWindow *cw)
{
  bool result = false;
  Ekiga::ServicePtr libnotify = cw->priv->core->get ("libnotify");

  if (libnotify) {

    boost::optional<bool> val = libnotify->get_bool_property ("actions");
    if (val) {

      result = *val;
    }
  }
  return result;
}
