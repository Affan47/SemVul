setIconOptions(Table table)
{
    pictureFilename = table.Query("Icon");
    picExtension = getExtension(pictureFilename);
    caption = table.Query("Caption");
    captionTip = table.Query("ToolTip.Caption");
    x = atoi(table.Query("X").c_str());
    y = atoi(table.Query("Y").c_str());
    width = atoi(table.Query("Width").c_str());
    height = atoi(table.Query("Height").c_str());

    if (table.ArrayExists("Command"))
        commandArray = table.QueryArray("Command");
    else if (table.Query("Command") != "")
        commandArray.push_back(table.Query("Command"));
}
