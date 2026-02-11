addOption(OptionPtr option)
{
    if (!option->longName().isEmpty())
        m_options[option->longName()] = option;
    if (!option->shortName().isEmpty())
        m_options[option->shortName()] = option;
}
