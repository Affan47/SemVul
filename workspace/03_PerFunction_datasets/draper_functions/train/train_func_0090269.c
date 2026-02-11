readDataTypes( FILE* typesFP )
{
  char* currentLine = (char*)malloc(1000);
  fData* data = (fData*)malloc(sizeof(fData));
  int i=0,j=0;
  char* c;

  if(!typesFP) return NULL;
  if( fgets( currentLine, 100, typesFP ) == NULL ) return NULL;

  sscanf( currentLine, "%d", &(data->numCols) );
  data->types = (fDataType*)malloc(sizeof(fDataType) * data->numCols);
  data->fieldNames = (char**)malloc(sizeof(char*) * data->numCols);
  for(i=0;i<data->numCols;i++)data->fieldNames[i] = (char*)malloc(1000);
  i=0;
  while(i<data->numCols)
    {
      if( fgets( currentLine, 100, typesFP ) == NULL ) return NULL;
      c = currentLine; j = 0;
      while(*c!='\t'&&*c!='\0') data->fieldNames[i][j++] = *(c++);
      data->fieldNames[i][j] = '\0';
      data->types[i++] = readDataType( c );
    }
  free(currentLine);
  return data;
}
