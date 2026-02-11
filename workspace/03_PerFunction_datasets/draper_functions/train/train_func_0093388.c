owned(FXObject * obj){
  if (hasClipboard() && obj==clipowner) return true;
  return false;
  }
