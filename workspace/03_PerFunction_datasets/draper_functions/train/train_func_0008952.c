parse_size(char *str) {
  size_t size = 0;

  if (strlen(str) >= 1)
  {
     int multiply = 0;

     switch(str[strlen(str)-1])
     {
       case '0':
       case '1':
       case '2':
       case '3':
       case '4':
       case '5':
       case '6':
       case '7':
       case '8':
       case '9':
         multiply = 1;
         break;
       case 'K':
       case 'k':
         multiply = 1024;
         break;
       case 'M':
       case 'm':
         multiply = 1024*1024;
         break;
       case 'G':
       case 'g':
         multiply = 1024*1024*1024;
         break;
       default:
         break;
     }

     size = atoll(str) * multiply;
  }

  return size;
}
