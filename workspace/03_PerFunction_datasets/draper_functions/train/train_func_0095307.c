SetContext(char *id)

{
InstallObject(id);

Verbose("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
Verbose(" * (Changing context state to: %s) *",id);
Verbose("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
strncpy(CONTEXTID,id,31);
}
