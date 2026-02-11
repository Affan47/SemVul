read_list( FILE *stream, int *num)


{
   int i, c;
   char temp[255],
       **list = NULL;
   int needright=1;

   *num = 0;

   while ( (c=fgetc(stream)) != EOF && c != '(' );
   if (c == EOF)
      return(NULL);

   list = (char **) malloc(sizeof(char *));

   do {
      fscanf(stream, "%s", temp);

      if(temp[0] == '(' ){
         needright++;
         list = (char **) realloc(list, ++(*num) * sizeof(char *));
         list[*num - 1] = (char *) malloc(2 * sizeof(char));
	 strcpy(list[*num - 1], "(");
	 if ((int) strlen(temp) > 1)
	    for (i=0;temp[i] != '\0';i++)temp[i]=temp[i+1];
	 else
	     fscanf(stream, "%s", temp);
      }

      for(i=0;temp[i] != '\0'; i++)
      if(temp[i] ==  ')' ){
         temp[i]='\0';
         if(needright-- > 1 ){
            if(i != 0){

	       list = (char **) realloc(list, ++(*num) * sizeof(char *));
	       list[*num - 1] = (char *) malloc((strlen(temp)+1) * sizeof(char));
	       strcpy(list[*num - 1], temp);
            }
	    strcpy(temp, ")" );
	 }
	 break;
       }

      if(temp[0] != '\0'){
         list = (char **) realloc(list, ++(*num )* sizeof(char *));
         list[*num - 1] = (char *) malloc((strlen(temp)+1) * sizeof(char));
	 strcpy(list[*num - 1], temp);

      }
   } while (needright);

   while( (c=fgetc(stream)) != EOF  && c != '\n' && c != ')' );

   return(list);
}
