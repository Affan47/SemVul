slashres(int res)
{
  int minbucket = 1;
  if (res < 2)
    return;
  else if (res < 4)
    minbucket=16;
  else if (res < 8)
    minbucket=4;
  for (int blockno=0; blockno<nb; blockno++)
    for (int buckno=minbucket; buckno<64; buckno++)
      blocks[blockno].zero(buckno);
}
