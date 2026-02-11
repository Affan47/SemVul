Tokenize( char* s, char*** tok )
{
  char test[MAX_LINE];
  char *sep = "\t \n!=";
  char *word;
  int count=0;

  strncpy( test, s, MAX_LINE );

  for( word = strtok(test, sep); word; word = strtok(NULL, sep) ) {
    strncpy( (*tok)[count], word, MAX_LINE );
    count++;
  }

  return count;
}
