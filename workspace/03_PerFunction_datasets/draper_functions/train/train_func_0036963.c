LeastSignificantBit(char bitmask) const
  {
    if(!bitmask) {
      qFatal("Tried to get least signifiant bit of empty bitmask");
    }

    for(int i=0; i<8; i++) {
      if(bitmask & (1 << i)) return i;
    }

    qFatal("Should never get here!");
    return 0xFF;
  }
