dropTargetScheme() const
{
    QString parsableScheme = "";

    QList< Token *> list = m_dropTarget->tokensAtRow();

    foreach( Token *token, list )
    {
        parsableScheme += typeElements[token->value()];
    }

    return parsableScheme;
}
