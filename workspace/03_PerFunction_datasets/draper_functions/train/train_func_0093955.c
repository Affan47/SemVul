dib7000m_autosearch_is_irq(struct dvb_frontend *demod)
{
	struct dib7000m_state *state = demod->demodulator_priv;
	if (state->revision == 0x4000)
		return dib7000m_autosearch_irq(state, 1793);
	else
		return dib7000m_autosearch_irq(state, 537);
}
