parser3(char *T) {

  Binder.prepare(T);


  if (Style12.match()) {
    parseStyle12(T);
    LastWasStyle12 = true;
    return true;
  }


  if (Style12BadHouse.match()) {
    attachHouseStock(Style12BadHouse,true);
    return true;
  }


  if (Style12House.match()) {
    attachHouseStock(Style12House,false);
    return true;
  }


  if (Seek.match()) {

    if (global.HideSeeks && global.IcsSeekGraph)
      return true;

    return(doOutput(T, -1, false, global.Colors.Seeks));
  }


  if (global.IcsSeekGraph) {

    if (SgClear.match()) {
      ensureSeekGraph();
      global.skgraph2->clear();
      return true;
    }

    if (SgAdd.match()) {
      seekAdd(SgAdd);
      return true;
    }

    if (SgAdd2.match()) {
      seekAdd(SgAdd2);
      return true;
    }

    if (SgRemove.match()) {
      seekRemove(SgRemove);
      return true;
    }
  } else {

    if (SgClear.match()) return true;
    if (SgAdd.match()) return true;
    if (SgAdd2.match()) return true;
    if (SgRemove.match()) return true;

  }


  if (SgRemove2.match()) return true;

  return(parser4(T));
}
