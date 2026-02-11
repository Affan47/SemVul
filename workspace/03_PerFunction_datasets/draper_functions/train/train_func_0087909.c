FoundAnyExcept (Editor* ed) {
    Component* comp = ed->GetComponent()->GetRoot();
    Iterator i;

    for (unidraw->First(i); !unidraw->Done(i); unidraw->Next(i)) {
        Editor* test_ed = unidraw->GetEditor(i);

        if (test_ed != ed) {
            Component* test_comp = test_ed->GetComponent();

            if (test_comp != nil && test_comp->GetRoot() == comp) {
                return true;
            }
        }
    }
    return false;
}
