SetComponent (Component* c) {
    Component* oldcomp = _component;
    _component = (c == nil) ? nil : c->GetRoot();

    for (UList* v = _vars->First(); v != _vars->End(); v = v->Next()) {
        ModifStatusVar* msv = var(v);

        if (msv != this && msv->GetComponent() == _component) {
            modified(msv->GetModifStatus());
            return;
        }
    }
    if (oldcomp != _component)
        modified(false);
}
