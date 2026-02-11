targetOfAccel(FXHotKey hotkey) const {
  if(hotkey){
    register FXuint p=(hotkey*13)&max;
    register FXuint c;
    FXASSERT(hotkey!=UNUSEDSLOT);
    FXASSERT(hotkey!=EMPTYSLOT);
    while((c=key[p].code)!=hotkey){
      if(c==UNUSEDSLOT) return NULL;
      p=(p+1)&max;
      }
    return key[p].target;
    }
  return NULL;
  }
