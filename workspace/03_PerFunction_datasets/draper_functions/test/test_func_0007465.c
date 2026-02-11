Pop()

{
    char *TypeIn;
    extern char *MenuPOP;

    MenuSelect(MenuPOP);
    if (Context == NULL)
        ShowPrompt("There isn't a context to pop to.");

    else {
        SQClear();
        if (WroteCell) {


            if (Not CDClose(Parameters.kpCellDesc))
                MallocFailed();
            Parameters.kpModified = False;
        }
        elif (Parameters.kpModified) {
            ShowPrompt("You've modified this cell.  Do you want to save it (y)?");
            TypeIn = FBEdit(NULL);
            if (TypeIn == NULL) {
                MenuDeselect(MenuPOP);
                ErasePrompt();
                return;
            }
            if (TypeIn[0] == 'n' Or TypeIn[0] == 'N') {
                if (Not CDClose(Parameters.kpCellDesc))
                    MallocFailed();
            }
            else
                Save();
        }
        edit_cell(pop_context());
    }
    TitleWindow();
    MenuDeselect(MenuPOP);
}
