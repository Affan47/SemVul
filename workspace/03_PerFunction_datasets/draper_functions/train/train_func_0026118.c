trim_text(char *s)
{   int i;
    if (strlen(s) < 128) { strcpy(trimmed_text, s); return; }
    for (i=0; i<120; i++) trimmed_text[i] = s[i];
    trimmed_text[i++] = '.';
    trimmed_text[i++] = '.';
    trimmed_text[i++] = '.';
    trimmed_text[i++] = 0;
    return;
}
