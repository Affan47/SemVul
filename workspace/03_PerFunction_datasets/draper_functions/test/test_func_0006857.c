operator<<(const QString& arg)
{
    if( program().isEmpty() )
        setShellCommand( arg );
    else
        AmarokProcess::operator<<( arg );
    return *this;
}
