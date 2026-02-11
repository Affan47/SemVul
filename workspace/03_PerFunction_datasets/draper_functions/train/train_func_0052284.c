Execute () {
    Clipboard* cb = GetClipboard();
    Editor* ed = GetEditor();

    if (cb == nil) {
        Selection* s = ed->GetSelection();

        if (s->IsEmpty()) {
            return;
        }

        SetClipboard(cb = new Clipboard);
	FrameIdrawView* top = (FrameIdrawView*)ed->GetViewer()->GetGraphicView();
	GraphicView* views = ((FrameEditor*)ed)->GetFrame();
        s->Sort(views);
        Iterator i;

        for (s->First(i); !s->Done(i); s->Next(i)) {
            s->GetView(i)->Interpret(this);
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
        ed->GetComponent()->Interpret(this);
    }
}
