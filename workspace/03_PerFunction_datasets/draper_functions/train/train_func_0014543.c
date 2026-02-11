calcDefaultDims() {
#if 0
  int w;

  if (options & FLAGS_NO_WORDWRAP)
    w=-1;
  else if (options & FLAGS_USE_FULL_WIDTH)
    w=width;
  else
    w=m_maxDefaultWidth;
  m_htmlCtx->layout(w-border*2, -1);
  m_defaultWidth=m_htmlCtx->getWidth();
  m_defaultHeight=m_htmlCtx->getHeight();
  m_haveDefaultDims=true;
#else
  int w;

  if (options & FLAGS_NO_WORDWRAP)
    w=-1;
  else if (options & FLAGS_USE_FULL_WIDTH)
    w=width;
  else if (m_maxDefaultWidth!=-1)
    w=m_maxDefaultWidth;
  else {
    int wTmp=1024;
    int mask=1024;
    int i;

    for (i=0; i<10; i++) {
      double ar, nw, nh;

      m_htmlCtx->layout(wTmp-border*2, -1);
      nw=(double) (m_htmlCtx->getWidth());
      nh=(double)(m_htmlCtx->getHeight());
      ar=nw/nh;

      if (ar>=3.5 && ar<4.0)
	break;

      if (ar>4.0)

	wTmp&=~mask;

      mask>>=1;
      wTmp|=mask;
    }
    w=wTmp;
  }


  m_htmlCtx->layout(w-border*2, -1);
  m_defaultWidth=m_htmlCtx->getWidth();
  m_defaultHeight=m_htmlCtx->getHeight();
  m_haveDefaultDims=true;

#endif
}
