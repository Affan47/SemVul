dg100_checksum(gbuint8 buf[], int count)
{
  gbuint16 sum = 0;
  int i;

  for (i = 0; i < count; i++) {
    sum += buf[i];
  }
  sum &= (1<<15) - 1;

  return(sum);
}
