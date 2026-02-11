slotConfigChanged( bool changed )
{
    m_configChanged = changed;
    if( changed )
        debug() << "config changed";
}
