hasAttr(const std::string& attr) const
{

    if (m_attrs.count(attr) > 0) {
        return true;
    } else if (m_type) {

        if (m_type->getAttribute(attr) != 0) {
            return true;
        }
    }
    return false;
}
