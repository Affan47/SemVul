offsetCol( int addCol) {

  if (addCol < 0) return;
  if ( colSave > 0)  colSave += addCol;
  if (acolSave > 0) acolSave += addCol;

}
