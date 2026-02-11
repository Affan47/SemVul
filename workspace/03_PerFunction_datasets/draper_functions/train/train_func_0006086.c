key_press(guint keyval, gchar *commit_str, gchar *preedit_str)
{
  char str[2];
  GooCanvasItem	*item = NULL;

  if(!gcomprisBoard)
    return FALSE;


  switch (keyval)
    {
    case GDK_Shift_L:
    case GDK_Shift_R:
    case GDK_Control_L:
    case GDK_Control_R:
    case GDK_Caps_Lock:
    case GDK_Shift_Lock:
    case GDK_Meta_L:
    case GDK_Meta_R:
    case GDK_Alt_L:
    case GDK_Alt_R:
    case GDK_Super_L:
    case GDK_Super_R:
    case GDK_Hyper_L:
    case GDK_Hyper_R:
    case GDK_Mode_switch:
    case GDK_dead_circumflex:
    case GDK_Num_Lock:
      return FALSE;
    case GDK_KP_Enter:
    case GDK_Return:
      process_ok();
      return TRUE;
    }

  sprintf(str, "%c", keyval);

  item = answer_item[current_focus];

  if(GOO_IS_CANVAS_TEXT(item))
    {
      gchar *oldtext;
      gchar *newtext;

      g_object_get (item, "text", &oldtext, NULL);

      switch(keyval)
	{
	case GDK_BackSpace:
	case GDK_Delete:

	  if(oldtext[1] != '\0')
	    newtext = g_strndup(oldtext, strlen(oldtext)-1);
	  else
	    newtext = "?";

	  break;

	default:

	  if(keyval<'0' || keyval>'9')
	    str[0]='0';

	  if(oldtext[0] == '?' && strlen(oldtext)==1)
	    {
	      oldtext[0] = ' ';
	      g_strstrip(oldtext);
	    }

	  if(strlen(oldtext)<2)
	    newtext = g_strconcat(oldtext, &str, NULL);
	  else
	    newtext = g_strdup(oldtext);
	  break;

	}

      if(newtext[0] != '?')
	answer[current_focus] = atoi(newtext);

      g_object_set (item,
			     "text", newtext,
			     NULL);

      g_free(oldtext);

      if(solution_found())
	{
	  gamewon = TRUE;
	  gc_bonus_display(gamewon, GC_BONUS_SMILEY);
	}
    }

  return TRUE;
}
