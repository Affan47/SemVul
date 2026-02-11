OnlyOneEditorOf (Component* c) {
    Component* comp = c->GetRoot();
    Iterator i;
    int count = 0;

    for (unidraw->First(i); !unidraw->Done(i) && count < 2; unidraw->Next(i)) {
        Component* test_comp = unidraw->GetEditor(i)->GetComponent();

        if (test_comp != nil && test_comp->GetRoot() == comp) {
            ++count;
        }
    }
    return count == 1;
}
