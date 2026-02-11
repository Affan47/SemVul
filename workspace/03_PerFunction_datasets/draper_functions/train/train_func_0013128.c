InvalidateRectangle(PRectangle rc) {
  if (wid)
    wid->update(rc.left, rc.top, rc.right - rc.left + 1, rc.bottom - rc.top + 1);
}
