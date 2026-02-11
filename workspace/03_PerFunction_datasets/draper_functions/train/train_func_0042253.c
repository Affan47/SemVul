FileWriteTo(const char *FName) {
    char Name[MAXPATH];

    if (ExpandPath(FName, Name, sizeof(Name)) == -1) {
        View->MView->Win->Choice(GPC_ERROR, "Error", 1, "O&K", "Invalid path: %s.", FName);
        return 0;
    }
    if (FindFile(Name) == 0) {
        if (FileExists(Name)) {
            switch (View->MView->Win->Choice(GPC_ERROR, "File Exists",
                           2,
                           "&Overwrite",
                           "&Cancel",
                           "%s", Name))
            {
            case 0:
                break;
            case 1:
            case -1:
            default:
                return 0;
            }
        }
        return SaveTo(Name);
    } else {
        View->MView->Win->Choice(GPC_ERROR, "Error", 1, "O&K", "Already editing '%s.'", Name);
        return 0;
    }
}
