main(int argc,char *argv[]) {
  char *name = NULL;
  int sensor = NXT_SENSOR1;
  int c, i, ret, newsensor;
  const char *device;

  while ((c = getopt(argc,argv,":hn:s:"))!=-1) {
    switch(c) {
      case 'h':
        usage(argv[0],0);
        break;
      case 'n':
        name = optarg;
        break;
      case 's':
        newsensor = atoi(optarg)-1;
        if (!NXT_VALID_SENSOR(newsensor)) {
          fprintf(stderr,"Invalid sensor: %s\n",optarg);
          usage(argv[0],1);
        }
        else {
          sensor = newsensor;
        }
        break;
      case ':':
        fprintf(stderr,"Option -%c requires an operand\n",optopt);
        usage(argv[0],1);
        break;
      case '?':
        fprintf(stderr,"Unrecognized option: -%c\n", optopt);
        usage(argv[0],1);
        break;
    }
  }

  nxt_t *nxt = nxt_open(name);
  if (nxt==NULL) {
    fprintf(stderr,"Could not find NXT\n");
    return 1;
  }

  for (i=0;i<0x100;i++) {
    printf("Scanning: 0x%02X %d%%\r",i,i*100/0x100);
    fflush(stdout);

    device = nxt_i2c_get_deviceid(nxt, sensor, i);
    nxt_wait_after_direct_command();
    if (device!=NULL) {
      printf("at I2C address 0x%02X: %s\n", i, device);
    }
  }

  ret = nxt_error(nxt);
  nxt_close(nxt);

  return ret;
}
