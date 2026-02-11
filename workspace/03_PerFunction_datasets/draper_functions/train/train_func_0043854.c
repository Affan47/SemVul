OnPageChanged( wxWizardExEvent& event ) {
    if (event.GetDirection() == false) return;

    wxASSERT(m_pTitleStaticCtrl);
    wxASSERT(m_pProgressIndicator);

    m_pTitleStaticCtrl->SetLabel(
        _("Communicating with project\nPlease wait...")
    );

    SetProjectPropertiesSucceeded(false);
    SetProjectPropertiesURLFailure(false);
    SetProjectPropertiesCommunicationFailure(false);
    SetProjectAccountCreationDisabled(false);
    SetProjectClientAccountCreationDisabled(false);
    SetNetworkConnectionNotDetected(false);
    SetNextState(PROJPROP_INIT);

    CProjectPropertiesPageEvent TransitionEvent(wxEVT_PROJECTPROPERTIES_STATECHANGE, this);
    AddPendingEvent(TransitionEvent);

    Fit();
}
