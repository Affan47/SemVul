tilingPatternFillL2(GfxState *state, Catalog *cat, Object *str,
				       double *pmat, int paintType, int tilingType, Dict *resDict,
				       double *mat, double *bbox,
				       int x0, int y0, int x1, int y1,
				       double xStep, double yStep) {
  PDFRectangle box;
  Gfx *gfx;

  if (paintType == 2) {

    writePS("currentcolor\n");
  }
  writePS("<<\n  /PatternType 1\n");
  writePSFmt("  /PaintType {0:d}\n", paintType);
  writePSFmt("  /TilingType {0:d}\n", tilingType);
  writePSFmt("  /BBox [{0:.6g} {1:.6g} {2:.6g} {3:.6g}]\n", bbox[0], bbox[1], bbox[2], bbox[3]);
  writePSFmt("  /XStep {0:.6g}\n", xStep);
  writePSFmt("  /YStep {0:.6g}\n", yStep);
  writePS("  /PaintProc { \n");
  box.x1 = bbox[0];
  box.y1 = bbox[1];
  box.x2 = bbox[2];
  box.y2 = bbox[3];
  gfx = new Gfx(doc, this, resDict, &box, NULL);
  inType3Char = gTrue;
  if (paintType == 2) {
    inUncoloredPattern = gTrue;

    writePS("/pdfLastFill true def\n");
    writePS("/pdfLastStroke true def\n");
  }
  gfx->display(str);
  if (paintType == 2) {
    inUncoloredPattern = gFalse;

    writePS("/pdfLastFill false def\n");
    writePS("/pdfLastStroke false def\n");
  }
  inType3Char = gFalse;
  delete gfx;
  writePS("  }\n");
  writePS(">>\n");
  writePSFmt("[{0:.6g} {1:.6g} {2:.6g} {3:.6g} {4:.6g} {5:.6g}]\n", mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
  writePS("makepattern setpattern\n");
  writePS("clippath fill\n");

  return gTrue;
}
