Unexecute() {
    OverlayViewer* v = (OverlayViewer*) GetEditor()->GetViewer();
    Perspective basep = *v->GetPerspective();
    basep.cury -= _px;
    basep.curx -= _py;
    v->Adjust(basep);
}
