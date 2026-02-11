read_ints(struct interrupt *interrupts, int calc_max) {
  char buf[256];
  int cur_no=0,count=-1;
  FILE *proc;

  if((proc=fopen("/proc/interrupts","rt"))==NULL) {
    fprintf(stderr,"cannot open /proc/interrupts for reading\n");
    return -1;
  }
  if (fgets(buf,sizeof(buf),proc)==NULL)
    return -1;
  while(cur_no<MAX_INTS) {
    char *tmpptr;
    if (fgets(buf,sizeof(buf),proc)==NULL)
      break;
    buf[strlen(buf)-1]=0;
    buf[3]=0;
    buf[15]=0;
    tmpptr=buf;
    while(tmpptr[0]==' ') tmpptr++;
    cur_no=atoi(tmpptr);
    if(!(cur_no>count))
      break;
    tmpptr=buf+4;
    while(tmpptr[0]==' ') tmpptr++;
    count=atoi(tmpptr);
    interrupts[cur_no].last_count=interrupts[cur_no].count;
    interrupts[cur_no].count=count;
    strncpy(interrupts[cur_no].name,buf+33,MAX_NAME_LEN+1);
    interrupts[cur_no].name[MAX_NAME_LEN]=0;
    if ((calc_max) && (interrupts[cur_no].last_count>0) && ((interrupts[cur_no].count-interrupts[cur_no].last_count)>interrupts[cur_no].max_rate))
      interrupts[cur_no].max_rate=interrupts[cur_no].count-interrupts[cur_no].last_count;
    count=cur_no;
  }
  interrupts[count+1].max_rate=-1;
  fclose(proc);
  return 0;
}
