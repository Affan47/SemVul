internalMessageFallback(KMessage::MessageType messageType, const QString &text, const QString &caption)
{
    QString prefix;
    switch(messageType)
    {
        case KMessage::Error:
             prefix = QLatin1String("ERROR: ");
             break;
        case KMessage::Fatal:
             prefix = QLatin1String("FATAL: ");
             break;
        case KMessage::Information:
             prefix = QLatin1String("INFORMATION: ");
             break;
        case KMessage::Sorry:
             prefix = QLatin1String("SORRY: ");
             break;
        case KMessage::Warning:
             prefix = QLatin1String("WARNING: ");
             break;
    }

    QString message;

    if( !caption.isEmpty() )
        message += QLatin1Char('(') + caption + QLatin1Char(')');

    message += prefix + text;


    std::cerr << "WARNING: Please setup an KMessageHandler with KMessage::setMessageHandler to display message propertly." << std::endl;

    std::cerr << qPrintable(message) << std::endl;
}
