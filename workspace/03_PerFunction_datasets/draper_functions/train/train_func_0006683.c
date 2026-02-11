release_weak (vaul_weak_notify *notify, void *data)
{
  for (weak **wp = &weaks; *wp; wp = &(*wp)->link)
    {
      weak *w = *wp;
      if (w->notify == notify && w->data == data)
	{
	  *wp = w->link;
	  delete w;
	  break;
	}
    }
}
