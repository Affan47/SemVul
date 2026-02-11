EventHandler(
             AuServer       *aud,
             AuEvent        *ev,
             AuEventHandlerRec *handler
             )
{
    MonitorDevicePtr priv = (MonitorDevicePtr) handler->data;

    switch (ev->type)
    {
      case AuEventTypeMonitorNotify:
	if (priv->callback)
	    (*priv->callback) (aud, handler, ev, priv->callback_data);
	break;
      case AuEventTypeElementNotify:
	{
	    AuElementNotifyEvent *event = (AuElementNotifyEvent *) ev;

	    if (event->kind == AuElementNotifyKindState &&
		event->cur_state == AuStateStop)
	    {
		if (priv->callback)
		    (*priv->callback) (aud, handler, ev,
				       priv->callback_data);

		AuUnregisterEventHandler(aud, handler);
		AuReleaseScratchFlow(aud, priv->flow, NULL);
		Aufree(priv);
	    }
	    break;
	}
    }

    return AuTrue;
}
