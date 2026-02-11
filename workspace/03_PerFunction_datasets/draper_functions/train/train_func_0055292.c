value(const CValue& value)
{
    if (!m_variables_pool->is_variable_exists(m_name))
    {
        m_variables_pool->add_variable(m_name, value);
    }
    else
    {
        m_variables_pool->get_variable(m_name).value(value);
    }
}
