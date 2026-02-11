Localize (Selection* s, Viewer* v) {
    Iterator i;

    for (s->First(i); !s->Done(i);) {
        GraphicView* view = s->GetView(i);

        if (view->GetViewer() != v) {
            s->Remove(i);
            view->EraseHandles();

        } else {
            s->Next(i);
        }
    }
}
