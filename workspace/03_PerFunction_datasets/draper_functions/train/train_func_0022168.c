SelectClipboard (Clipboard* cb, Editor* ed) {
    Selection* s = ed->GetSelection();
    s->Clear();
    Viewer* viewer;
    Iterator i;

    for (int j = 0; (viewer = ed->GetViewer(j)) != nil; ++j) {
        for (cb->First(i); !cb->Done(i); cb->Next(i)) {
            GraphicView* views = viewer->GetGraphicView();
            GraphicView* view = views->GetGraphicView(cb->GetComp(i));

            if (view != nil) s->Append(view);
        }
    }
}
