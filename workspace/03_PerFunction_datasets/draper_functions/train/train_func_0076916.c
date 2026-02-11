rewind()
{
  JASSERT(lseek(_fd,0,SEEK_SET) == 0)(strerror(errno)).Text("Cannot rewind");
}
