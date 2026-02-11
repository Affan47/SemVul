changed ()
{
	trace_with_mask("PropertyBox::changed",GUITRACE);

	m_apply_button->set_sensitive (true);
	m_property_changed = true;
}
