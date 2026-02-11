saveLockState(bool lockState)
{
    Database db = Database(ideskrcFile);
    Table & table = db.Query("Config");

    if(table.isValid())
    {
        if (lockState)
            table.Set("Locked", "true");
        else
            table.Set("Locked", "false");

        db.Write();
    }
    else
    {
        cout << "Incorrect config file\n";
        return;
    }

}
