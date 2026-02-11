walkForward1() {
  if (!mygame)
    return;
  freeze();
  mygame->goForward1();
  position= mygame->getCurrentPosition();
  setInfo(2,position.getLastMove());
  setInfo(4,position.getMaterialString(mygame->Variant));
  setInfo(5,position.getHouseString());
  queueRepaint();
  thaw();
}
