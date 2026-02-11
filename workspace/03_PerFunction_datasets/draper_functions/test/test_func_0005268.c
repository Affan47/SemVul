mg_findS2O(void)
{
  if (!(_mgc->has & HAS_S2O)) {
    if (!_mgc->xstk->hasinv) {
      TmInvert(_mgc->xstk->T, _mgc->xstk->Tinv);
      _mgc->xstk->hasinv = 1;
    }
    TmConcat(_mgc->S2W, _mgc->xstk->Tinv, _mgc->S2O);
    TmConcat(_mgc->xstk->T, _mgc->W2S, _mgc->O2S);
    _mgc->has |= HAS_S2O;
  }
}
