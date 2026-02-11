onKeyRelease(FXObject* sender,FXSelector,void* ptr){
  FXTRACE((200,"%p->FXAccelTable::onKeyRelease keysym=0x%04x state=%04x\n",this,((FXEvent*)ptr)->code,((FXEvent*)ptr)->state));
  register FXEvent* event=(FXEvent*)ptr;
  register FXuint code=MKUINT(event->code,event->state&(SHIFTMASK|CONTROLMASK|ALTMASK|METAMASK));
  register FXuint p=(code*13)&max;
  register FXuint c;
  FXASSERT(code!=UNUSEDSLOT);
  FXASSERT(code!=EMPTYSLOT);
  while((c=key[p].code)!=code){
    if(c==UNUSEDSLOT) return 0;
    p=(p+1)&max;
    }
  if(key[p].target && key[p].messageup){
    key[p].target->tryHandle(sender,key[p].messageup,ptr);
    }
  return 1;
  }
