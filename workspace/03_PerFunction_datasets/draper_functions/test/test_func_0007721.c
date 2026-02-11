slotProviderLoaded(KNS::Provider *provider)
{
    if (m_command == command_download) {
        loadEntries(provider);
    } else if (m_command == command_upload) {


        m_providers.append(provider);
    } else {
        kError() << "Engine: invalid command" << endl;
    }
}
