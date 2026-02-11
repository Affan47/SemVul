setV(va_list arg)
      {
        bool value = va_arg(arg, int) != 0;
#       ifdef OFX_DEBUG_PARAMETERS
        std::cout << value;
#       endif
        return set(value);
      }
