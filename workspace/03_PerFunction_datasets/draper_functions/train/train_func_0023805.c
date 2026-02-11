Execute () {
    Editor* ed = GetEditor();
    Component* comp = ed->GetComponent();
    Catalog* catalog = unidraw->GetCatalog();
    const char* name = catalog->GetName(comp);
    ModifStatusVar* mv = (ModifStatusVar*) ed->GetState("ModifStatusVar");

    if (name != nil && (mv == nil || mv->GetModifStatus())) {
        char buf[CHARBUFSIZE];
        strcpy(buf, name);

        ConfirmDialog dialog("Really revert to last version saved?");
        ed->InsertDialog(&dialog);
        char confirmation = dialog.Confirm();
        ed->RemoveDialog(&dialog);

        if (confirmation == 'y') {
            Component* orig = comp;
            catalog->Forget(orig);

            if (unidraw->GetCatalog()->Retrieve(buf, comp)) {
                ed->SetComponent(comp);
                unidraw->CloseDependents(orig);
                unidraw->Update();

                CompNameVar* cv = (CompNameVar*) ed->GetState("CompNameVar");

                if (cv != nil) cv->SetComponent(comp);
                if (mv != nil) mv->SetComponent(comp);

                Component* root = orig->GetRoot();
                delete root;

            } else {
                ConfirmDialog dialog(
                    "Couldn't revert! (File nonexistent?)", "Save changes?"
                );
                ed->InsertDialog(&dialog);
                char confirmation = dialog.Confirm();
                ed->RemoveDialog(&dialog);

                UpdateCompNameVars();
                if (mv != nil) mv->Notify();

                if (confirmation == 'y') {
                    SaveCompAsCmd saveCompAs(ed);
                    saveCompAs.Execute();
                }
            }
        }
    }
}
