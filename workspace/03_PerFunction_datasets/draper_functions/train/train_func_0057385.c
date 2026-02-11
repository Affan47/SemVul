debugInfo() const
{
    QString info;
    info += QLatin1String("### Source: ###################\n");
    if (!source().isNull())
        info += QLatin1String("source: #") + source() + QLatin1String("#\n");
    if (!url().isNull())
        info += QLatin1String("url: #") + url() + QLatin1String("#\n");
    info += QLatin1String("### Source end ################\n");
    return info;
}


}
