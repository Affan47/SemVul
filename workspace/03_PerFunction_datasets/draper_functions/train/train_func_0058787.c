toString() const
{
    DOMString result = "<!DOCTYPE ";
    result += m_qualifiedName;
    if (!m_publicId.isEmpty()) {
	result += " PUBLIC \"";
	result += m_publicId;
	result += "\" \"";
	result += m_systemId;
	result += "\"";
    } else if (!m_systemId.isEmpty()) {
	result += " SYSTEM \"";
	result += m_systemId;
	result += "\"";
    }

    if (!m_subset.isEmpty()) {
	result += " [";
	result += m_subset;
	result += "]";
    }

    result += ">";

    return result;
}
