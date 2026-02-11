Attach (ComponentView* view) {
    _views->Prepend(new UList(view));
    view->SetSubject(this);
}
