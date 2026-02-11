createFromXml( QXmlStreamReader *reader )
{
    Dynamic::BiasPtr bias( createBias() );
    bias->fromXml( reader );
    return bias;
}
