addQuad(const dimeVec3f &v0,
		      const dimeVec3f &v1,
		      const dimeVec3f &v2,
		      const dimeVec3f &v3,
		      const dimeMatrix * const matrix)
{
  if (this->fillmode) {
    if (matrix) {
      dimeVec3f t0, t1, t2, t3;
      matrix->multMatrixVec(v0, t0);
      matrix->multMatrixVec(v1, t1);
      matrix->multMatrixVec(v2, t2);
      matrix->multMatrixVec(v3, t3);
      faceindices.append(facebsp.addPoint(t0));
      faceindices.append(facebsp.addPoint(t1));
      faceindices.append(facebsp.addPoint(t2));
      faceindices.append(facebsp.addPoint(t3));
      faceindices.append(-1);
    }
    else {
      faceindices.append(facebsp.addPoint(v0));
      faceindices.append(facebsp.addPoint(v1));
      faceindices.append(facebsp.addPoint(v2));
      faceindices.append(facebsp.addPoint(v3));
      faceindices.append(-1);
    }
  }
  else {
    this->addLine(v0, v1, matrix);
    this->addLine(v1, v2, matrix);
    this->addLine(v2, v3, matrix);
    this->addLine(v3, v0, matrix);
  }
}
