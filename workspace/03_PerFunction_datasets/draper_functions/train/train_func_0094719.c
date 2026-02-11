parse()
{
    const uint length = m_expression.length();
    for( uint pos = 0; pos < length; ++pos )
        parseChar( m_expression.at( pos ) );
    finishedToken();
    finishedOrGroup();

    return m_parsed;
}
