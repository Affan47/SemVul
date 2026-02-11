p_upd_sensitivity(GapModFramesGlobalParams *gmop)
{
  GtkWidget  *wgt;
  gboolean    l_sensitive;
  gboolean    l_sensitive_frame;
  const char *l_label_name;

  l_sensitive = FALSE;
  switch(gmop->sel_mode)
  {
    case GAP_MTCH_EQUAL:
    case GAP_MTCH_START:
    case GAP_MTCH_END:
    case GAP_MTCH_ANYWHERE:


      l_sensitive = TRUE;
      break;
    default:
      break;
  }
  wgt = gmop->case_sensitive_check_button;
  if(wgt)
  {
    gtk_widget_set_sensitive(wgt, l_sensitive);
  }

  l_sensitive = TRUE;
  if(gmop->sel_mode == GAP_MTCH_ALL_VISIBLE)
  {

     l_sensitive = FALSE;
  }
  wgt = gmop->layer_pattern_entry;
  if(wgt)
  {
    gtk_widget_set_sensitive(wgt, l_sensitive);
  }


  l_sensitive = FALSE;
  l_sensitive_frame = TRUE;
  l_label_name = " ";
  switch(gmop->action_mode)
  {
    case GAP_MOD_ACM_DUPLICATE:
    case GAP_MOD_ACM_RENAME:
      l_label_name = _("New Layer Name");
      l_sensitive = TRUE;
      break;
    case GAP_MOD_ACM_MERGE_EXPAND:
    case GAP_MOD_ACM_MERGE_IMG:
    case GAP_MOD_ACM_MERGE_BG:
      l_label_name = _("Merged Layer Name");
      l_sensitive = TRUE;
      break;
    case GAP_MOD_ACM_SEL_SAVE:
    case GAP_MOD_ACM_SEL_LOAD:
    case GAP_MOD_ACM_SEL_DELETE:
      l_sensitive_frame = FALSE;
      l_label_name = _("Channel Name");
      l_sensitive = TRUE;
      break;
    case GAP_MOD_ACM_SEL_REPLACE:
    case GAP_MOD_ACM_SEL_ADD:
    case GAP_MOD_ACM_SEL_SUBTRACT:
    case GAP_MOD_ACM_SEL_INTERSECT:
    case GAP_MOD_ACM_SEL_NONE:
    case GAP_MOD_ACM_SEL_ALL:
    case GAP_MOD_ACM_SEL_INVERT:
      l_sensitive_frame = FALSE;
      break;
    default:
      break;
  }

  wgt = gmop->new_layername_entry;
  if(wgt)
  {
    gtk_widget_set_sensitive(wgt, l_sensitive);
  }

  wgt = gmop->layer_selection_frame;
  if(wgt)
  {
    gtk_widget_set_sensitive(wgt, l_sensitive_frame);
  }

  wgt = gmop->new_layername_label;
  if(wgt)
  {
    gtk_label_set_text(GTK_LABEL(wgt), l_label_name);
  }


}
