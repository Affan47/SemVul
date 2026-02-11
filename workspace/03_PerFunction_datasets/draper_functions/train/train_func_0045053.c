integrateV(OfxTime time1, OfxTime time2, va_list arg)
      {
        double *value1 = va_arg(arg, double*);
        double *value2 = va_arg(arg, double*);
        double *value3 = va_arg(arg, double*);
        OfxStatus stat = integrate(time1, time2, *value1, *value2, *value3);
#       ifdef OFX_DEBUG_PARAMETERS
        if (stat == kOfxStatOK) {
          std::cout << ' ' << *value1 << ' ' << *value2 << ' ' << *value3;
        }
#       endif
        return stat;
      }
