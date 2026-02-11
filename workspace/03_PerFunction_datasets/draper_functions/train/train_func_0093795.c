mgicchikn_util_get_rc_shadow_width (MgicChiknRcStyle * rc_style,
									GtkStyle * style,
									GtkWidget * widget,
									GtkStateType * state,
									GtkShadowType shadow_type,
									gint * xthickness,
									gint * ythickness)
{
	g_return_if_fail (style != NULL);
	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (xthickness != NULL);
	g_return_if_fail (ythickness != NULL);

	if (rc_style == NULL || !MGICCHIKN_IS_RC_STYLE (rc_style)
		|| widget == NULL || !GTK_IS_WIDGET (widget))
	{
		*xthickness = style->xthickness;
		*ythickness = style->ythickness;
		return;
	}


	if (!GTK_WIDGET_IS_SENSITIVE (widget))
		*state = GTK_STATE_INSENSITIVE;

	if (rc_style->shadow_width[*state][shadow_type] >= 0)
	{
		*xthickness = rc_style->shadow_width[*state][shadow_type];
		*ythickness = rc_style->shadow_width[*state][shadow_type];
	}
	else
	{
		*xthickness = style->xthickness;
		*ythickness = style->ythickness;
	}
}
