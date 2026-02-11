InitialiseSourceBlocks(vector<DataBlock>::iterator &sourceblock, u64 blocksize)
{
  for (u32 blocknum=0; blocknum<blockcount; blocknum++)
  {

    sourceblock->SetLocation(diskfile,
                             blocknum * blocksize);
    sourceblock->SetLength(min(blocksize, filesize - (u64)blocknum * blocksize));
    sourceblock++;
  }
}
