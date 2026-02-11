svdLoadSparseBinaryFile(FILE *file) {
  int rows, cols, vals, n, c, i, v, r, e = 0;
  float f;
  SMat S;
  e += svd_readBinInt(file, &rows);
  e += svd_readBinInt(file, &cols);
  e += svd_readBinInt(file, &vals);
  if (e) {
    svd_error("svdLoadSparseBinaryFile: bad file format");
    return NULL;
  }

  S = svdNewSMat(rows, cols, vals);
  if (!S) return NULL;

  for (c = 0, v = 0; c < cols; c++) {
    if (svd_readBinInt(file, &n)) {
      svd_error("svdLoadSparseBinaryFile: bad file format");
      return NULL;
    }
    S->pointr[c] = v;
    for (i = 0; i < n; i++, v++) {
      e += svd_readBinInt(file, &r);
      e += svd_readBinFloat(file, &f);
      if (e) {
        svd_error("svdLoadSparseBinaryFile: bad file format");
        return NULL;
      }
      S->rowind[v] = r;
      S->value[v] = f;
    }
  }
  S->pointr[cols] = vals;
  return S;
}
