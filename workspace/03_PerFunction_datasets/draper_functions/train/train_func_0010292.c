open(const char *filename, const Mode mode)
{
  f = fopen(filename, "rb");

  if(f == NULL)
    switch(errno) {
    case ENOENT: err |= NotFound; break;
    case EACCES: err |= Denied; break;
    default: err |= NotOpen; break;
    }
}
