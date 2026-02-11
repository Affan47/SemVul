readisaac (struct isaac *isaac, unsigned char *p, size_t size)
{
  size_t inbytes = isaac->buffered;

  while (true)
    {
      if (size <= inbytes)
        {
          memcpy (p, isaac->data.b + ISAAC_BYTES - inbytes, size);
          isaac->buffered = inbytes - size;
          return;
        }

      memcpy (p, isaac->data.b + ISAAC_BYTES - inbytes, inbytes);
      p += inbytes;
      size -= inbytes;


      if (ALIGNED_POINTER (p, isaac_word))
        {
          isaac_word *wp = (isaac_word *) p;
          while (ISAAC_BYTES <= size)
            {
              isaac_refill (&isaac->state, wp);
              wp += ISAAC_WORDS;
              size -= ISAAC_BYTES;
              if (size == 0)
                {
                  isaac->buffered = 0;
                  return;
                }
            }
          p = (unsigned char *) wp;
        }

      isaac_refill (&isaac->state, isaac->data.w);
      inbytes = ISAAC_BYTES;
    }
}
