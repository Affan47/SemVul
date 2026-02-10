activateMenuOption (void)
{
    System::getInstance ().removeActiveState (false);
    System::getInstance ().setActiveState (
            new TournamentSetupState (*m_SelectedOption));
}
