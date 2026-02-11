keywork()
{
  uint8 key;
  bool pressed;
  for (;;) {
    key_decode(&key,&pressed);
    switch (key) {
    case '<':
      if (pressed) {
	shipmove=-1;
      }else{
	if (shipmove==-1) shipmove=0;
      };
      break;
    case '>':
      if (pressed) {
	shipmove=1;
      }else{
	if (shipmove==1) shipmove=0;
      };
      break;
    case ' ':
      {
	uint8 i;
	if (!pressed) break;
	for (i=0;i<NUMSHOTS;++i) {
	  if (shots[i].x==-1) {
	    shots[i].x=ship;
	    shots[i].y=24;
	    break;
	  };
	};
      };
      break;
    case 'x':
      return;
    case '@':
      if (pressed) {
        reboot();
      }
      break;
    case 'u':
      if (pressed) {
        changecolors(+1);
      }
      break;
    case 'd':
      if (pressed) {
        changecolors(-1);
      }
      break;
    case '0':
      if (pressed) {
        if (psychedelic==false) psychedelic=true;
        else {
          psychedelic=false;
          shotcolor=4,shipcolor=5,aliencolor=3;
        }
      }
      break;
    case 'p':
      if (pressed) {
        displaypause();
      }
      break;
    };
  };
}
