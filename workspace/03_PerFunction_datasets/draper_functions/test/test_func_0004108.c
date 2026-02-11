_v_set (HpAccessorVector this, unsigned char * data, unsigned short val)
{
  val &= this->mask;

  if (this->mask <= 255)
    {
      data[0] = (unsigned char)val;
    }
  else
    {
#ifndef NotOrig
      data[1] = (unsigned char)val;
      data[0] = (unsigned char)(val >> 8);
#else
      data[0] = (unsigned char)val;
      data[1] = (unsigned char)(val >> 8);
#endif
    }
}
