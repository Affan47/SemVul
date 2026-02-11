Update () {
    Selection* s = GetSelection();
    GraphicView* view = GetGraphicView();
    Component* viewComp = view->GetGraphicComp();
    Component* edComp = _editor->GetComponent();

    if (viewComp != edComp) {
        ComponentView* newView = edComp->Create(ViewCategory());

        if (newView->IsA(GRAPHIC_VIEW)) {
            edComp->Attach(newView);
            newView->Update();
            SetGraphicView((GraphicView*) newView);

        } else {
            delete newView;
        }

    } else {
	s->Hide(this);
        _viewerView->Update();
        GraphicBlock::UpdatePerspective();
	_damage->Repair();
        s->Show(this);
    }
}
