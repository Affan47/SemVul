setParameter(std::string param,
                                float value)
{
    if (!m_handle) return;

    for (unsigned int i = 0; i < m_descriptor->parameterCount; ++i) {
        if (param == m_descriptor->parameters[i]->identifier) {
            m_descriptor->setParameter(m_handle, i, value);
            return;
        }
    }
}
