Execute() {
    FrameEditor* ed = (FrameEditor*) GetEditor();
    FrameIdrawComp *comp = ((FrameIdrawComp*)ed->GetComponent());
    ed->GetViewer()->GetSelection()->Clear();
    FramesView* fv = (FramesView*)ed->GetViewer()->GetGraphicView();
    Iterator frameptr;
    fv->SetView( ed->GetFrame(), frameptr );
    Damage* damage = ed->GetViewer()->GetDamage();
    damage->Incur(ed->GetFrame()->GetGraphic());
    int before = fv->Index(frameptr);
    fv->First(frameptr);
    fv->Next(frameptr);
    if (fv->Done(frameptr))
        fv->First(frameptr);
    int after = fv->Index(frameptr);
    ed->SetFrame((FrameView*)fv->GetView(frameptr));
    damage->Incur(ed->GetFrame()->GetGraphic());
    ed->UpdateFrame(true);
    FrameNumberState* fnumstate = ed->framenumstate();
    int fnum = fv->Index(frameptr);
    fnumstate->framenumber(fnum);
    _requestmotion = before-after;
    _actualmotion = Math::abs(_requestmotion);
    const char* funcformat = AbsMoveFuncFormat();
    ComTerpServ* comterp = ed->GetComTerp();
    if (funcformat && comterp) {
      char buf[BUFSIZ];
      sprintf(buf, funcformat, _allowbg ? 0 : 1);
      ComValue retval (comterp->run(buf));
    }
    unidraw->Update();
}
