update() {
  memcpy(planetable[plane],in,geo.size);

  if(stock<PLANES) stock++;

  if(mode) {
    if(timer) {
      readplane = readplane + stride;
      while(readplane < 0) readplane += stock;
      while(readplane >= stock) readplane -= stock;
      timer--;
    } else {
      readplane = fastrand() % stock;
      stride = fastrand() % 5 - 2;
      if(stride >= 0) stride++;
      timer = fastrand() % 6 + 2;
    }
  } else
    if(stock > 0)
      readplane = fastrand() % stock;

  plane++;
  if(plane==PLANES) plane=0;

  memcpy(out,planetable[readplane],geo.size);

}
