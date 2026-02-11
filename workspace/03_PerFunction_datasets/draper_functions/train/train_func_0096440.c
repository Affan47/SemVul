Execute () {
    Editor* ed = GetEditor();
    Iterator i;
    unidraw->First(i);
    unidraw->Next(i);

    if (!unidraw->Done(i)) {
	ModifStatusVar* mv = (ModifStatusVar*) ed->GetState("ModifStatusVar");

	if (mv != nil && mv->GetModifStatus() && !FoundAnyExcept(ed)) {
            ConfirmDialog dialog("Save changes?");

	    ed->InsertDialog(&dialog);
	    char resp = dialog.Confirm();
	    ed->RemoveDialog(&dialog);

	    if (resp == '\007') {
		return;

            } else if (resp == 'y') {
		SaveCompCmd saveComp(ed);
		saveComp.Execute();

                if (mv->GetModifStatus()) {
                    return;
                }
	    }
	}
        unidraw->Close(ed);
    }
}
