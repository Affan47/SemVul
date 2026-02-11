Execute() {

    OverlayRasterRect* rr = _comp->GetOverlayRasterRect();

    if (!_orig) {
        _orig = rr->GetOriginal();
        _orig->ref();
    }

    rr->SetRaster( _nras );

    _comp->Notify();
    unidraw->Update();

}
