dereference_ffitype(String *ffitype) {
   char *start;
   char *temp = Char(ffitype);
   String *reduced_type = 0;

   if(temp && temp[0] == '(' && temp[1] == '*') {
      temp += 2;


      while(*temp == ' ') temp++;
      start = temp;

      reduced_type = NewString(start);
      temp = Char(reduced_type);

      while(*temp != '\0') temp++;
      *(--temp) = '\0';
   }

   return reduced_type ? reduced_type : Copy(ffitype);
}
