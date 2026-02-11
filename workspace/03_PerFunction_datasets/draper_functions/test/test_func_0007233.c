draw(Gfx *gfx, GBool printing) {
  Object obj;
  double ca = 1;

  if (!isVisible (printing))
    return;

  if (appearance.isNull()) {
    ca = opacity;

    appearBuf = new GooString ();

    appearBuf->append ("q\n");
    if (color)
      setColor(color, gTrue);
    else
      appearBuf->append ("1 1 1 rg\n");
    if (!name->cmp("Speaker"))
      appearBuf->append (ANNOT_SOUND_AP_SPEAKER);
    else if (!name->cmp("Mic"))
      appearBuf->append (ANNOT_SOUND_AP_MIC);
    appearBuf->append ("Q\n");

    double bbox[4];
    bbox[0] = bbox[1] = 0;
    bbox[2] = bbox[3] = 24;
    if (ca == 1) {
      createForm(bbox, gFalse, NULL, &appearance);
    } else {
      Object aStream, resDict;

      createForm(bbox, gTrue, NULL, &aStream);
      delete appearBuf;

      appearBuf = new GooString ("/GS0 gs\n/Fm0 Do");
      createResourcesDict("Fm0", &aStream, "GS0", ca, NULL, &resDict);
      createForm(bbox, gFalse, &resDict, &appearance);
    }
    delete appearBuf;
  }


  appearance.fetch(xref, &obj);
  gfx->drawAnnot(&obj, border, color,
		 rect->x1, rect->y1, rect->x2, rect->y2);
  obj.free();
}
