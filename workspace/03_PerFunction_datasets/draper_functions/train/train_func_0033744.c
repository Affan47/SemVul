interpolation_completed_cb (MxAdjustment *adj, MxKineticScrollView *scroll)
{
  MxKineticScrollViewPrivate *priv = scroll->priv;
  MxAdjustment *hadj, *vadj;

  g_signal_handlers_disconnect_by_func (adj, interpolation_completed_cb,
                                        scroll);

  mx_scrollable_get_adjustments (MX_SCROLLABLE (scroll), &hadj, &vadj);
  if (adj == hadj)
    priv->hclamping = FALSE;
  else
    priv->vclamping = FALSE;

  if (!priv->hclamping && !priv->vclamping && \
      priv->state == MX_KINETIC_SCROLL_VIEW_STATE_CLAMPING)
    set_state (scroll, MX_KINETIC_SCROLL_VIEW_STATE_IDLE);
}
