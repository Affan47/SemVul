main(int argc, char **argv) {
  struct termios term;
  struct interrupt interrupts[MAX_INTS];
  int loop=-1,active=1,count;
  char key;

  memset(interrupts,0,sizeof(interrupts));
  for(count=1;count<argc;count++) {
    if (strcmp(argv[count],"-a")==0)
      active=0;
    else if ((strcmp(argv[count],"-n")==0) && (count+1<argc)){
      loop=atoi(argv[++count]);
    }
    else
      help(argv[0]);
  }
  if (loop<0) {
    tcgetattr(fileno(stdin),&term);
    term.c_lflag &= ~(ICANON);
    tcsetattr(fileno(stdin),0,&term);
    fcntl(fileno(stdin),F_SETFL,O_NONBLOCK);
  }
  read_ints(interrupts,0);
  sleep(1);
  while(loop) {
    if ((loop<0) && (read(fileno(stdin),&key,1)==1)) {
      switch(key) {
      case 'a':
	if (active != 0) active=0;
	else active=1;
	break;
      case 't':
	system("top");
	break;
      case 'q':
	loop=0;
	break;
      default:
	fcntl(fileno(stdin),F_GETFL,count);
	fcntl(fileno(stdin),F_SETFL,count&~O_NONBLOCK);
	ihelp(active);
	fcntl(fileno(stdin),F_SETFL,O_NONBLOCK);
	break;
      }
      read_ints(interrupts,0);
    }
    else {
      read_ints(interrupts,1);
      if (loop)
	printf(CLEAR);
      print_ints(interrupts,active);
    }
    if (loop)
      sleep(1);
    if (loop>0)
      loop--;
  }
  fcntl(fileno(stdin),F_GETFL,count);
  fcntl(fileno(stdin),F_SETFL,count&~O_NONBLOCK);
  term.c_lflag |= ICANON;
  tcsetattr(fileno(stdin),0,&term);
  printf("\n");
  return 0;
}
