selectCharacter (void)
{


    if ( allCharactersSelected () )
    {
        setTimeToWait (0);
        return;
    }

    SelectedCharacter selectedCharacter;
    selectedCharacter.col = getSelectedCol ();
    selectedCharacter.index = getSelectedCharacterIndex ();
    selectedCharacter.row = getSelectedRow ();
    m_SelectedCharacters.push_back (selectedCharacter);

    setNextPlayer ();
    if ( allCharactersSelected () )
    {
        setTimeToWait (k_TimeToWait);
    }
    else
    {
        selectFirstCharacter ();
    }
}
