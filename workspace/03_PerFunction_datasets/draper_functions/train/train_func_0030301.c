movePressed(But *but)  {
  EditToolWin  *etw = but_packet(but);
  SgfElem  *active, *loSwap, *hiSwap, *prevChild;

  assert(MAGIC(etw));
  etw->modified = TRUE;
  active = etw->sgf->active;
  assert(active->childH != active->childT);
  assert(active->childH != NULL);
  hiSwap = active->activeChild;
  if (active->childH == hiSwap)  {
    loSwap = hiSwap;
    hiSwap = loSwap->sibling;
  } else  {
    for (loSwap = active->childH;
	 loSwap->sibling != hiSwap;
	 loSwap = loSwap->sibling)
      assert(MAGIC(loSwap));
  }
  if (active->childH == loSwap)  {
    active->childH = hiSwap;
  } else  {
    for (prevChild = active->childH;
	 prevChild->sibling != loSwap;
	 prevChild = prevChild->sibling);
    prevChild->sibling = hiSwap;
  }
  loSwap->sibling = hiSwap->sibling;
  hiSwap->sibling = loSwap;
  if (active->childT == hiSwap)
    active->childT = loSwap;
  sgfMap_remap(etw->sgfMap, etw->sgf);
  butCan_resizeWin(etw->mapWin->win, but_w(etw->sgfMap), but_h(etw->sgfMap),
		   TRUE);
  return(0);
}
