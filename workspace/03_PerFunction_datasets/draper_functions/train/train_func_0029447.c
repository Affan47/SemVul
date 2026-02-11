save()
{
    m_config.setUsername( m_configDialog->kcfg_GpodderUsername->text() );
    m_config.setPassword( m_configDialog->kcfg_GpodderPassword->text() );
    m_config.setEnableProvider( m_enableProvider );
    m_config.setIgnoreWallet( false );

    m_config.save();
    KCModule::save();
}
