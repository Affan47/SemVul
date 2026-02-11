Init (Interactor* i) {
    SetClassName("OverlaySlider");
    interactor = i;
    view = i->GetPerspective();
    view->Attach(this);
    shown = new Perspective;
    constrained = false;
    moveType = MOVE_UNDEF;
    *shown = *view;
    shape->vstretch = shape->vshrink = 0;
    prevl = prevb = prevr = prevt = 0;
    input = new Sensor(updownEvents);
}
