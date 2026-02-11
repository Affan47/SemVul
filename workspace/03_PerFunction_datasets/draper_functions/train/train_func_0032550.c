enterNotify(const XEvent *pEvent_)
{ if (pEvent_->xcrossing.mode==NotifyNormal) processFocusIn(); }
