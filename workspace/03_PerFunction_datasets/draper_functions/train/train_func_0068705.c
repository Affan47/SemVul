OutputLibraries(struct __ecereNameSpace__ecere__com__Instance * f, struct __ecereNameSpace__ecere__com__Instance * libraries)
{
{
char ** item;
struct __ecereNameSpace__ecere__com__Instance * __internalArray = (libraries);

for(item = (char **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array; item < (char **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array + ((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->count; item++)
{
char ext[17];
char temp[797];
char * s = (*item);
unsigned int usedFunction = 0x0;

__ecereFunction___ecereNameSpace__ecere__sys__GetExtension((*item), ext);
if(!strcmp(ext, "o") || !strcmp(ext, "a"))
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(f, " ");
else
{
if(!strcmp(ext, "so") || !strcmp(ext, "dylib"))
{
if(!strncmp((*item), "lib", 3))
strcpy(temp, (*item) + 3);
else
strcpy(temp, (*item));
__ecereFunction___ecereNameSpace__ecere__sys__StripExtension(temp);
s = temp;
}
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(f, " \\\n\t$(call _L,");
usedFunction = 0x1;
}
EscapeForMakeToFile(f, s, 0x0, 0x0, 0x0);
if(usedFunction)
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(f, ")");
}
}
}
