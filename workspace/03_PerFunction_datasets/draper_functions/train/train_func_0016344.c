gamgi_io_token_check (const char *string)
{
char *delimiters = GAMGI_IO_DELIMITERS;
char buffer[GAMGI_ENGINE_LINE];


if (gamgi_io_token_size_check (string, GAMGI_ENGINE_LINE) == FALSE) return TRUE;


strcpy (buffer, string);
if (strtok (buffer, delimiters) == NULL) return FALSE;
else return TRUE;
}
