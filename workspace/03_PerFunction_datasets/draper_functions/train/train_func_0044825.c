check_for_selection_change (AtkObject   *accessible,
                            GtkWidget   *widget)
{
  EelEditableLabelAccessiblePrivate *priv;
  EelEditableLabel *label;
  gboolean ret_val = FALSE;

  priv = g_object_get_data (G_OBJECT (accessible), eel_editable_label_accessible_data);
  label = EEL_EDITABLE_LABEL (widget);

  if (label->selection_anchor != label->selection_end)
    {
      if (label->selection_anchor != priv->selection_anchor ||
          label->selection_end != priv->selection_end)


        ret_val = TRUE;
    }
  else
    {

      ret_val = (priv->selection_anchor != priv->selection_end);
    }
  priv->selection_anchor = label->selection_anchor;
  priv->selection_end = label->selection_end;

  return ret_val;
}
