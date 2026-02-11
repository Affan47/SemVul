UpdateCompNameVars () {
    Iterator i;

    for (unidraw->First(i); !unidraw->Done(i); unidraw->Next(i)) {
        Editor* ed = unidraw->GetEditor(i);
        CompNameVar* compNameVar = (CompNameVar*) ed->GetState("CompNameVar");
        if (compNameVar != nil) compNameVar->UpdateName();
    }
}
