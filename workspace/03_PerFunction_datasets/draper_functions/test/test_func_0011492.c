ConfQuit(GxView *V, int multiFile) {
    if (Modified) {
        if (multiFile) {
            switch (V->Choice(GPC_ERROR,
                              "File Modified",
                              5,
                              "&Save",
                              "&As",
                              "A&ll",
                              "&Discard",
                              "&Cancel",
                              "%s", FileName))
            {
            case 0:
                if (Save() == 0) return 0;
                break;
            case 1:
                {
                    char FName[MAXPATH];
                    strcpy(FName, FileName);
                    if (V->GetFile("Save As", sizeof(FName), FName, HIST_PATH, GF_SAVEAS) == 0) return 0;
                    if (FileSaveAs(FName) == 0) return 0;
                }
                break;
            case 2:
                return -2;
            case 3:
                break;
            case 4:
            case -1:
            default:
                return 0;
            }
        }else {
            switch (V->Choice(GPC_ERROR,
                              "File Modified",
                              4,
                              "&Save",
                              "&As",
                              "&Discard",
                              "&Cancel",
                              "%s", FileName))
            {
            case 0:
                if (Save() == 0) return 0;
                break;
            case 1:
                {
                    char FName[MAXPATH];
                    strcpy(FName, FileName);
                    if (V->GetFile("Save As", sizeof(FName), FName, HIST_PATH, GF_SAVEAS) == 0) return 0;
                    if (FileSaveAs(FName) == 0) return 0;
                }
                break;
            case 2:
                break;
            case 3:
            case -1:
            default:
                return 0;
            }
        }
    }
    return 1;
}
