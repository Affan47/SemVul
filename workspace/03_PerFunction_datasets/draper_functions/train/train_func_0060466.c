on_clicked_trigger_presentity (Ekiga::Presentity* presentity)
{
  Ekiga::TriggerMenuBuilder builder;

  presentity->populate_menu (builder);
}
