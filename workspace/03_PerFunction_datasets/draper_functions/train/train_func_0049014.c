Execute () {
    Editor* ed = GetEditor();
    Editor* newEd = new IdrawEditor(GetGraphicComp());

    *newEd->GetState("ModifStatusVar") = *ed->GetState("ModifStatusVar");

    unidraw->Open(newEd);
}
