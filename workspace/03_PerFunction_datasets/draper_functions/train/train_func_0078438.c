writeStdin (const QString &line)
{
    return write( codec->fromUnicode( line + '\n' ) ) > 0;
}
