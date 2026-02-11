Tohexstr(char *input, char *output)
{
     if ( (input == NULL) || (output == NULL) )
	  return;

     if (acceptable_inited == FALSE)
	  init_acceptable();

     while (*input) {

	  if (acceptable[(int)*input] == TRUE) {
	       *output++ = *input++;
	  }
	  else {
	       *output++ = '%';
	       *output++ = hex[*input >> 4];
	       *output++ = hex[*input & 15];
	       input++;
	  }
     }

     *output = '\0';
}
