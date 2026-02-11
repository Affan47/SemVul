gamgi_io_token_float_get_check (const char *token,
float *real, const float min, const float max)
{
char *end;


errno = 0;

*real = (float) strtod (token, &end);


if (*end != '\0') return FALSE;


if (errno == ERANGE) return FALSE;


if (*real < min) return FALSE;
if (*real > max) return FALSE;

return TRUE;
}
