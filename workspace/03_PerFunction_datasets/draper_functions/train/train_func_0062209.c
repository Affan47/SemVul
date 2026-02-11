file_table_print(void)
{
  int fileID;
  int lprintHeader = 1;
  bfile_t *fileptr;

  for ( fileID = 0; fileID < _file_max; fileID++ )
    {
      fileptr = file_to_pointer(fileID);

      if ( fileptr )
	{
	  if ( lprintHeader )
	    {
	      fprintf(stderr, "\nFile table:\n");
	      fprintf(stderr, "+-----+---------+");
	      fprintf(stderr, "----------------------------------------------------+\n");
	      fprintf(stderr, "|  ID |  Mode   |");
	      fprintf(stderr, "  Name                                              |\n");
	      fprintf(stderr, "+-----+---------+");
	      fprintf(stderr, "----------------------------------------------------+\n");
	      lprintHeader = 0;
	    }

	  fprintf(stderr, "| %3d | ", fileID);

	  switch ( fileptr->mode )
	    {
	    case 'r':
	      fprintf(stderr, "read   ");
	      break;
	    case 'w':
	      fprintf(stderr, "write  ");
	      break;
	    case 'a':
	      fprintf(stderr, "append ");
	      break;
	    default:
	      fprintf(stderr, "unknown");
	    }

          fprintf(stderr, " | %-51s|\n", fileptr->name);
	}
    }

  if ( lprintHeader == 0 )
    {
      fprintf(stderr, "+-----+---------+");
      fprintf(stderr, "----------------------------------------------------+\n");
    }
}
