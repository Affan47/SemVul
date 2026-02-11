isDangerousMove() const
{
    bool result = false;
    if (m_active != m_units.end()) {
        result = (*m_active)->isPushing();
    }
    return result;
}
