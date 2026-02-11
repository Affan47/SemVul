twiddler_chord_to_int(char *chord)
{
   char *convert = "0LMR";
   char *tmp;
   int result = 0;
   int shift = 0;

   if (strlen(chord)!=4) return -1;

   while (*chord) {
      if (!(tmp = strchr(convert, *chord))) return -1;
      result |= (tmp-convert)<<shift;
      chord++;
      shift += 2;
   }
   return result;
}
