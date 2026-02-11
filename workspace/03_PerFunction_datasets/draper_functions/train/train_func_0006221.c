SaveTutorialsData()
{
    static SqlStatementID updTutorial ;
    static SqlStatementID insTutorial ;

    switch (m_tutorialState)
    {
        case TUTORIALDATA_CHANGED:
        {
            SqlStatement stmt = CharacterDatabase.CreateStatement(updTutorial, "UPDATE character_tutorial SET tut0=?, tut1=?, tut2=?, tut3=?, tut4=?, tut5=?, tut6=?, tut7=? WHERE account = ?");
            for (int i = 0; i < 8; ++i)
                stmt.addUInt32(m_Tutorials[i]);

            stmt.addUInt32(GetAccountId());
            stmt.Execute();
        }
        break;

        case TUTORIALDATA_NEW:
        {
            SqlStatement stmt = CharacterDatabase.CreateStatement(insTutorial, "INSERT INTO character_tutorial (account,tut0,tut1,tut2,tut3,tut4,tut5,tut6,tut7) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

            stmt.addUInt32(GetAccountId());
            for (int i = 0; i < 8; ++i)
                stmt.addUInt32(m_Tutorials[i]);

            stmt.Execute();
        }
        break;
        case TUTORIALDATA_UNCHANGED:
            break;
    }

    m_tutorialState = TUTORIALDATA_UNCHANGED;
}
