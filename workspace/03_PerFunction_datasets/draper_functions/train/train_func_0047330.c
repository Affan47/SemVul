turnports_randomize(turnports* tp) {
  if(tp) {
    unsigned int size=(unsigned int)(tp->high-tp->low);
    unsigned int i=0;
    unsigned int cycles=size*10;
    for(i=0;i<cycles;i++) {
      u16bits port1 = (u16bits)(tp->low + (u16bits)(((unsigned long)random())%((unsigned long)size)));
      u16bits port2 = (u16bits)(tp->low + (u16bits)(((unsigned long)random())%((unsigned long)size)));
      if(port1!=port2) {
    	  int pos1=tp->status[port1];
    	  int pos2=tp->status[port2];
    	  int tmp=(int)tp->status[port1];
    	  tp->status[port1]=tp->status[port2];
    	  tp->status[port2]=(u32bits)tmp;
    	  tmp=(int)tp->ports[pos1];
    	  tp->ports[pos1]=tp->ports[pos2];
    	  tp->ports[pos2]=(u16bits)tmp;
      }
    }
  }
}
