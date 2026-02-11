key_set_contains_key (GSList                          *key_set,
			  const Accessibility_DeviceEvent *key_event)
{
  gint i;
  gint len;
  GSList *l;

  if (!key_set)
    {
#ifdef SPI_DEBUG
      g_print ("null key set!\n");
#endif
      return TRUE;
    }

  len = g_slist_length (key_set);

  if (len == 0)
    {
#ifdef SPI_DEBUG
      g_print ("anykey\n");
#endif
      return TRUE;
    }

  for (l = key_set,i = 0; l; l = g_slist_next(l),i++)
    {
      Accessibility_KeyDefinition *kd = l->data;
#ifdef SPI_KEYEVENT_DEBUG
      g_print ("key_set[%d] event = %d, code = %d; key_event %d, code %d, string %s\n",
                i,
                (int) kd->keysym,
                (int) kd->keycode,
                (int) key_event->id,
                (int) key_event->hw_code,
                key_event->event_string);
#endif
      if (kd->keysym == (dbus_uint32_t) key_event->id)
        {
          return TRUE;
	}
      if (kd->keycode == (dbus_uint32_t) key_event->hw_code)
        {
          return TRUE;
	}
      if (key_event->event_string && key_event->event_string[0] &&
	  !strcmp (kd->keystring, key_event->event_string))
        {
          return TRUE;
	}
    }

  return FALSE;
}
