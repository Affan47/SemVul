setYearNumber( int newYear )
{
    const QString yearString = QString::number( newYear );

    Meta::YearPtr yearPtr = Meta::PrivateMetaRegistry::instance()->year( m_serviceName, yearString );
    if ( !yearPtr ) {
        ScriptableServiceInternalYear * intYear = new ScriptableServiceInternalYear( yearString );
        intYear->setServiceName( m_serviceName );
        intYear->setServiceDescription( m_serviceDescription );
        intYear->setServiceEmblem( m_serviceEmblem );
        intYear->setServiceScalableEmblem( m_serviceScalableEmblem );
        yearPtr = Meta::YearPtr( intYear );
        Meta::PrivateMetaRegistry::instance()->insertYear( m_serviceName, yearString, yearPtr );
    }

    setYear( yearPtr );
}
