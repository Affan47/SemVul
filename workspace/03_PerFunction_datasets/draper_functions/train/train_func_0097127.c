Execute () {
    Editor* ed = GetEditor();
    Editor* newEd = new FrameEditor((OverlayComp*)GetGraphicComp());

    *newEd->GetState("ModifStatusVar") = *ed->GetState("ModifStatusVar");

    unidraw->Open(newEd);
}
