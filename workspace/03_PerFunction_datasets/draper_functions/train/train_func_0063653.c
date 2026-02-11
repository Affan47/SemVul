context() const
{
    int len = 60;


    int signedPosition = m_finder.position();
    bool begin = (signedPosition - len/2)<=0;


    QString buffer = m_buffer;
    Word word = wordAtPosition( m_finder.position() );
    buffer = buffer.replace( word.start, word.word.length(),
                             QString::fromLatin1( "<b>%1</b>" ).arg( word.word ) );

    QString context;
    if ( begin )
        context = QString::fromLatin1("%1...")
                  .arg( buffer.mid(  0, len ) );
    else
        context = QString::fromLatin1("...%1...")
                  .arg( buffer.mid(  m_finder.position() - 20, len ) );

    context.replace( QLatin1Char('\n'), QLatin1Char(' ') );

    return context;
}
