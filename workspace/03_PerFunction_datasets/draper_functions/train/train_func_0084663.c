fffr8r8(double *input,
            long ntodo,
            double scale,
            double zero,
            int nullcheck,


            double nullval,
            char *nullarray,
            int  *anynull,
            double *output,
            int *status)


{
    long ii;
    short *sptr, iret;

    if (nullcheck == 0)
    {
        if (scale == 1. && zero == 0.)
        {
            memcpy(output, input, ntodo * sizeof(double) );
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++)
            {
                output[ii] = input[ii] * scale + zero;
            }
        }
    }
    else
    {
        sptr = (short *) input;

#if BYTESWAPPED && MACHINE != VAXVMS && MACHINE != ALPHAVMS
        sptr += 3;
#endif

        if (scale == 1. && zero == 0.)
        {
            for (ii = 0; ii < ntodo; ii++, sptr += 4)
            {
              if (0 != (iret = dnan(*sptr)) )
              {
                  if (iret == 1)
                  {
                    *anynull = 1;
                    if (nullcheck == 1)
                        output[ii] = nullval;
                    else
                    {
                        nullarray[ii] = 1;

                        output[ii] = DOUBLENULLVALUE;
                    }
                  }
                  else
                     output[ii] = 0;
              }
              else
                  output[ii] = input[ii];
            }
        }
        else
        {
            for (ii = 0; ii < ntodo; ii++, sptr += 4)
            {
              if (0 != (iret = dnan(*sptr)) )
              {
                  if (iret == 1)
                  {
                    *anynull = 1;
                    if (nullcheck == 1)
                        output[ii] = nullval;
                    else
                    {
                        nullarray[ii] = 1;

                        output[ii] = DOUBLENULLVALUE;
                    }
                  }
                  else
                     output[ii] = zero;
              }
              else
                  output[ii] = input[ii] * scale + zero;
            }
        }
    }
    return(*status);
}
