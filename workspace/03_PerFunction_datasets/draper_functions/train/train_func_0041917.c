DeleteFromDB()
{
    static SqlStatementID delItem ;

    SqlStatement stmt = CharacterDatabase.CreateStatement(delItem, "DELETE FROM item_instance WHERE guid = ?");
    stmt.PExecute(GetGUIDLow());
}
