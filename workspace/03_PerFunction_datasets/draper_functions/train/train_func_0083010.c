ShowHandles (Viewer* viewer) {
    Iterator i;

    for (First(i); !Done(i); Next(i)) {
        OverlayView* view = GetView(i);

	if (view->Highlightable())
	    continue;

        if (viewer == nil || view->GetViewer() == viewer)
	    if (HandlesEnabled())
		view->RedrawHandles();
    }
}
