setActive(Client *client)
{
  if (active != client)
    {
      guiUpdateLater();
      if (active)
        active->deActivate();
      if (client)
        active = client;
      if (active)
        active->reActivate();
    }
}
