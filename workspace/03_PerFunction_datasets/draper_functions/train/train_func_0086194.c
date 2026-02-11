Execute () {
    Editor* ed = GetEditor();

    Selection* s = ed->GetSelection();
    if (s->IsEmpty()) {
	return;
    }

    Iterator i;
    for (s->First(i); !s->Done(i); s->Next(i)) {
	GraphicView* view = s->GetView(i);
	view->GetSubject()->Interpret(this);
    }

    s->Clear();
    unidraw->Update();

    return;
}
