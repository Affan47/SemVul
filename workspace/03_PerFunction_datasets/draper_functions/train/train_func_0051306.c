GetLeaf (OverlayView* ov) {
    Iterator i;
    ov->First(i);

    if (!ov->Done(i)) {
        ov = GetLeaf((OverlayView*) ov->GetView(i));
    }

    return ov;
}
