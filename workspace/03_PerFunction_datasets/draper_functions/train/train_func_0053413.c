ParseDecimal(const char **data)
   {
      double decimal = 0.0;
      double factor = 0.1;
      while (**data != 0 && **data >= '0' && **data <= '9')
      {
         int digit = (*(*data)++ - '0');
         decimal = decimal + digit * factor;
         factor *= 0.1;
      }
      return decimal;
   }
