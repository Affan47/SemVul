cl_com_transformXML2String(const char* input, char** output) {
   int i,pos,s;
   int input_length = 0;
   int output_length = 0;
   int seq_count;
   int matched;

   if (input == NULL || output == NULL || *output != NULL) {
      return CL_RETVAL_PARAMS;
   }

   input_length = strlen(input);


   output_length = input_length;
   *output = (char*)malloc((sizeof(char) * (1 + output_length)));
   if (*output == NULL) {
      return CL_RETVAL_MALLOC;
   }

   pos = 0;
   seq_count = 0;
   for (i=0;i<input_length;i++) {
      if ( input[i] == '&' ) {

         for (s=0;s<CL_XML_SEQUENCE_ARRAY_SIZE;s++) {
            matched = 0;
            for (seq_count=0; i + seq_count < input_length && seq_count < cl_com_sequence_array[s].sequence_length ; seq_count++) {
               if (input[i+seq_count] != cl_com_sequence_array[s].sequence[seq_count]) {
                  break;
               }
               if ( seq_count + 1 == cl_com_sequence_array[s].sequence_length ) {

                  (*output)[pos++] = cl_com_sequence_array[s].character;
                  i += cl_com_sequence_array[s].sequence_length - 1;
                  matched = 1;
                  break;
               }
            }
            if (matched == 1) {
               break;
            }
         }
         continue;
      }
      (*output)[pos++] = input[i];
   }
   (*output)[pos] = '\0';
   return CL_RETVAL_OK;
}
