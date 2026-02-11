e_cal_component_abort_sequence (ECalComponent *comp)
{
	ECalComponentPrivate *priv;

	g_return_if_fail (comp != NULL);
	g_return_if_fail (E_IS_CAL_COMPONENT (comp));

	priv = comp->priv;

	priv->need_sequence_inc = FALSE;
}
