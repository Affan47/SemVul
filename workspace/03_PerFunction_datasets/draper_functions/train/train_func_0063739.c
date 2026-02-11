read_array (void* x,
                          size_t size,
                          size_t align,
                          ACE_CDR::ULong length)
{
  if (length == 0)
    return true;
  char* buf = 0;

  if (this->adjust (size * length, align, buf) == 0)
    {
#if defined (ACE_DISABLE_SWAP_ON_READ)
      ACE_OS::memcpy (x, buf, size*length);
#else
      if (!this->do_byte_swap_ || size == 1)
        ACE_OS::memcpy (x, buf, size*length);
      else
        {
          char *target = reinterpret_cast<char*> (x);
          switch (size)
            {
            case 2:
              ACE_CDR::swap_2_array (buf, target, length);
              break;
            case 4:
              ACE_CDR::swap_4_array (buf, target, length);
              break;
            case 8:
              ACE_CDR::swap_8_array (buf, target, length);
              break;
            case 16:
              ACE_CDR::swap_16_array (buf, target, length);
              break;
            default:

              this->good_bit_ = false;
              return false;
            }
        }
#endif
      return this->good_bit_;
    }
  return false;
}
