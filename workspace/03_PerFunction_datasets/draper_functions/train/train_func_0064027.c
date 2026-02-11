scriptmatch(char* s){
int pos = 0;

while (s[pos] == ' ') pos++;
if (s[pos] == '/') pos++;

if (s[pos] == '\0' || (s[pos] != 's' && s[pos] != 'S')) return MODE_PLAIN;
pos++;
if (s[pos] == '\0' || (s[pos] != 'c' && s[pos] != 'C')) return MODE_PLAIN;
pos++;
if (s[pos] == '\0' || (s[pos] != 'r' && s[pos] != 'R')) return MODE_PLAIN;
pos++;
if (s[pos] == '\0' || (s[pos] != 'i' && s[pos] != 'I')) return MODE_PLAIN;
pos++;
if (s[pos] == '\0' || (s[pos] != 'p' && s[pos] != 'P')) return MODE_PLAIN;
pos++;
if (s[pos] == '\0' || (s[pos] != 't' && s[pos] != 'T')) return MODE_PLAIN;

return MODE_SCRIPT;
}
