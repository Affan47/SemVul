get_canonical_option_prefix()
    {
        if (m_style & allow_long)
            return allow_long;

        if (m_style & allow_long_disguise)
            return allow_long_disguise;

        if ((m_style & allow_short) && (m_style & allow_dash_for_short))
            return allow_dash_for_short;

        if ((m_style & allow_short) && (m_style & allow_slash_for_short))
            return allow_slash_for_short;

        return 0;
    }
