_matewnck_application_process_property_notify (MatewnckApplication *app,
                                           XEvent          *xevent)
{


  if (xevent->xproperty.atom == XA_WM_NAME ||
      xevent->xproperty.atom ==
      _matewnck_atom_get ("_NET_WM_NAME") ||
      xevent->xproperty.atom ==
      _matewnck_atom_get ("_NET_WM_VISIBLE_NAME"))
    {

    }
  else if (xevent->xproperty.atom ==
           XA_WM_ICON_NAME ||
           xevent->xproperty.atom ==
           _matewnck_atom_get ("_NET_WM_ICON_NAME") ||
           xevent->xproperty.atom ==
           _matewnck_atom_get ("_NET_WM_VISIBLE_ICON_NAME"))
    {

    }
  else if (xevent->xproperty.atom ==
           _matewnck_atom_get ("_NET_WM_ICON") ||
           xevent->xproperty.atom ==
           _matewnck_atom_get ("KWM_WIN_ICON") ||
           xevent->xproperty.atom ==
           _matewnck_atom_get ("WM_NORMAL_HINTS"))
    {
      _matewnck_icon_cache_property_changed (app->priv->icon_cache,
                                         xevent->xproperty.atom);
      emit_icon_changed (app);
    }
  else if (xevent->xproperty.atom ==
           _matewnck_atom_get ("_NET_STARTUP_ID"))
    {

    }
}
