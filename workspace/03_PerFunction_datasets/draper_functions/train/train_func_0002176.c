show_info_level_1( definitionInfoT *info )
{
  uint32_t i = 0, index = 0;
  double resolution = info->timerResolution;
  double fileSize = info->traceFileSize;
  char* unitTimer;
  char* unitFileSize;


  while( (resolution / 1000 >= 1.0) && (i < 4) )
  {
    resolution /= 1000;
    i++;
  }
  switch( i )
  {
    case 0: unitTimer = "Hz";break;
    case 1: unitTimer = "KHz";break;
    case 2: unitTimer = "MHz";break;
    default: unitTimer = "GHz";break;
  }


  i = 0;
  while( (fileSize / 1024 >= 1.0) && (i < 5) )
  {
    fileSize /= 1024;
    i++;
  }
  switch( i )
  {
    case 0: unitFileSize = "Bytes"; break;
    case 1: unitFileSize = "KB"; break;
    case 2: unitFileSize = "MB"; break;
    case 3: unitFileSize = "GB"; break;
    default: unitFileSize = "TB";break;
  }

  printf( "\n##############" );
  printf( "\n#info level 1#" );
  printf( "\n##############\n" );
  printf( "+-------------------------------------------------------------------------------\n" );
  printf( "| general information \n" );
  printf( "+----------------------+--------------------------------------------------------\n" );
  printf( "| tracefile name       | %s\n", info->filePrefix );
  printf( "| creator of the trace | %s\n", info->creatorName );
  printf( "| trace unique id      | %lli\n", (unsigned long long int)info->traceUniqueId );
  printf( "| used OTF version     | %i.%i.%i %s\n", info->otfVersionMajor,
          info->otfVersionMinor, info->otfVersionSub, info->otfVersionString );
  printf( "| event files size     | %.2f %s\n", fileSize,unitFileSize );
  printf( "| process definitions  | %llu\n",
          (unsigned long long)info->counterProcessDefinition );
  printf( "| timer resolution     | %.2f %s\n",resolution,unitTimer );
  printf( "+----------------------+--------------------------------------------------------\n" );
  index = info->counterDefinitionComment;
  printf( "| definition comments\n" );
  printf( "+-------------------------------------------------------------------------------\n" );
  for( i = 0; i < index; i++ )
  {
    printf( "| %s\n", info->definitionComments[i] );
  }
  printf( "+-------------------------------------------------------------------------------\n" );
  printf( "\n" );
}
