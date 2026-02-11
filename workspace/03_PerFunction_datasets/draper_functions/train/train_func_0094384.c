Execute () {
    Clipboard* cb = GetClipboard();

    if (cb == nil) {
        SetClipboard(cb = new Clipboard);
        Editor* ed = GetEditor();
        Selection* s = ed->GetSelection();

        if (s->Number() > 1) {
            Iterator i;
            GraphicView* views = ed->GetViewer()->GetGraphicView();
            s->Sort(views);

            for (s->First(i); !s->Done(i); s->Next(i)) {
                s->GetView(i)->Interpret(this);
            }
        }

    } else {
        Clipboard* oldcb = cb;
        SetClipboard(cb = new Clipboard);

        Iterator i;
        for (oldcb->First(i); !oldcb->Done(i); oldcb->Next(i)) {
            oldcb->GetComp(i)->Interpret(this);
        }
        delete oldcb;
    }

    if (!cb->IsEmpty()) {
        if (_group == nil) {
            SetGroup(new GraphicComps);
        }
        _group->Interpret(this);
        _executed = true;
    }
}
