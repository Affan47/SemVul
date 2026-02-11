setXForm(XForm *xform) const
{
  if (iXForm && --iXForm->iRefCount == 0)
    delete iXForm;
  iXForm = xform;
  if (iXForm) {
    iXForm->iRefCount = 1;
    iDepth = iXForm->iStretch * iXForm->iDepth / 100.0;
    iHeight = iXForm->iStretch * iXForm->iBBox.height() - iDepth;
    if (!isMinipage())
      iWidth = iXForm->iStretch * iXForm->iBBox.width();
  }
}
