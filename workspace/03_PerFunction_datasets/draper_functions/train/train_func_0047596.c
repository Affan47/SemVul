start()
{
    if( m_mode == Interactive )
    {
        m_providersPage = new ChooseProvidersPage();
        m_providersPage.data()->setFields( Controller::availableFields(), m_checkedFields );
        m_providersPage.data()->setProvidersModel( m_providersModel, m_providersModel->selectionModel() );

        connect( m_providersPage.data(), SIGNAL(accepted()), SLOT(slotMatchTracks()) );
        connect( m_providersPage.data(), SIGNAL(rejected()), SLOT(slotSaveSizeAndDelete()) );
        m_dialog.data()->mainWidget()->hide();
        m_dialog.data()->setMainWidget( m_providersPage.data() );
        raise();
    }
    else if( m_checkedFields )
        slotMatchTracks();
}
