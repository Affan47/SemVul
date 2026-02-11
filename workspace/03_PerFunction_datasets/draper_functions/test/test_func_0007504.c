buffer_predelete_cb(int pos, int nDeleted, void *cbArg) {
  Fl_Text_Display *textD = (Fl_Text_Display *)cbArg;
  if (textD->mContinuousWrap) {


    IS_UTF8_ALIGNED2(textD->buffer(), pos)
    textD->measure_deleted_lines(pos, nDeleted);
  } else {
    textD->mSuppressResync = 0;
  }
}
