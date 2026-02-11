write_packed(unsigned char *data, int size, std::ofstream &f)
   {
      unsigned char c = 0;

      int bitshift = 7;
      for (int pos = 0; pos < size; pos++) {
         c = c | (data[pos] << bitshift);
         bitshift--;
         if ((bitshift == -1) || (pos == size-1)) {
            f.put(c);
            bitshift = 7;
            c = 0;
         }
      }
   }
