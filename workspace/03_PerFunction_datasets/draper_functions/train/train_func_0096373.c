GPS_Course_Lap_New(void)
{
  GPS_PCourse_Lap ret;

  if (!(ret=(GPS_PCourse_Lap)calloc(1,sizeof(GPS_OCourse_Lap)))) {
    perror("malloc");
    fprintf(stderr,"GPS_Course_Lap_New: Insufficient memory");
    fflush(stderr);
    return NULL;
  }

  return ret;
}
