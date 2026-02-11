calcInverse(void) const
{


  const float VALID_LIMIT = 1.0e-12f;

  if (this->invertedmatrix[0][0] == INVALID_TAG) {
    if (SbAbs(this->matrix.det4()) > VALID_LIMIT) {
      const_cast<SbXfBox3f *>(this)->invertedmatrix = this->matrix.inverse();
    }
    else {
#if COIN_DEBUG && 0
      const SbMatrix & m = this->matrix;
      SoDebugError::postWarning("SbXfBox3f::setTransform",
                                "invalid matrix (can't be inverted)");
      SoDebugError::postWarning("SbXfBox3f::setTransform",
                                "%f %f %f %f",
                                m[0][0], m[0][1], m[0][2], m[0][3]);
      SoDebugError::postWarning("SbXfBox3f::setTransform",
                                "%f %f %f %f",
                                m[1][0], m[1][1], m[1][2], m[1][3]);
      SoDebugError::postWarning("SbXfBox3f::setTransform",
                                "%f %f %f %f",
                                m[2][0], m[2][1], m[2][2], m[2][3]);
      SoDebugError::postWarning("SbXfBox3f::setTransform",
                                "%f %f %f %f",
                                m[3][0], m[3][1], m[3][2], m[3][3]);
#endif


      SbXfBox3f * thisp = const_cast<SbXfBox3f *>(this);
      *thisp = SbXfBox3f(this->project());


    }
  }
}
