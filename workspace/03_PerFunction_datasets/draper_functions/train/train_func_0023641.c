__ecereProp_CompilerType_Set_char__PTR_(char *  value)
{
if(value)
{
int c;

for(c = __ecereProp___ecereNameSpace__ecere__com__Platform_Set_char__PTR_(__ecereProp_CompilerType_Get_char__PTR_(firstCompilerType)); c <= __ecereProp___ecereNameSpace__ecere__com__Platform_Set_char__PTR_(__ecereProp_CompilerType_Get_char__PTR_(lastCompilerType)); c++)
if(!(strcasecmp)(value, compilerTypeNames[__ecereProp_CompilerType_Set_char__PTR_(__ecereProp___ecereNameSpace__ecere__com__Platform_Get_char__PTR_(c))]))
return __ecereProp_CompilerType_Set_char__PTR_(__ecereProp___ecereNameSpace__ecere__com__Platform_Get_char__PTR_(c));
}
return 0;
}
