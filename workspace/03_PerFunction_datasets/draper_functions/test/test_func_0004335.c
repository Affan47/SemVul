jchmod_(char * filename, char * char_mode, long l1, long l2)
{
mode_t mode = 0;
int i, status = 0;
char * name;

    if( (*char_mode) == '0' )
    {
      for( i = 0; i < l2; i++)
        mode = (mode*8) + (*(char_mode+i)-'0');
    }
    else
    {
      for( i = 0; i < l2; i++)
        mode = (mode*10) + (*(char_mode+i)-'0');
    }

    name = (char*) malloc(l1+1);
    for( i = 0; i < l1; i++)
      name[i] = filename[i];
    name[l1] = '\0';

    status = chmod(name, mode);
    if( status ) {
      perror("JCHMOD error");
      exit(1);
    }

    free(name);

    return (fortint) status;
}
