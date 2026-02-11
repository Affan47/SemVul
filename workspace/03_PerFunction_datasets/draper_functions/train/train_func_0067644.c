reset()
{
    if (m_type == FILE) {


	if (!m_value.isEmpty()) {
	    m_value = DOMString();
	    setChanged();
	}
    } else {
	setValue(getAttribute(ATTR_VALUE));
    }
    m_useDefaultChecked = true;
    m_checked = m_defaultChecked;
    setIndeterminate(true);
}
