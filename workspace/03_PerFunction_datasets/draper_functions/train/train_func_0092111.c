IOReady()
{
   return seek_pos==pos || stream->fd!=-1;
}
