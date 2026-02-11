qos_sprintfcheck() {
  char buf[128];
  char buf2[128];
  sprintf(buf, "%p", buf);
  sprintf(buf2, "%p", buf2);
  if((strcmp(buf, buf2) == 0) || (strlen(buf) < 4)) {

    return 0;
  }
  return 1;
}
