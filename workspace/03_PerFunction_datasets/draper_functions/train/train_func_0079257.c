changeState() {

  if(_state == CLOSED){
    open();
    _owner->hideConfigure(this);
  }
  else{
    close();
    _owner->hideConfigure(this);

  }
}
