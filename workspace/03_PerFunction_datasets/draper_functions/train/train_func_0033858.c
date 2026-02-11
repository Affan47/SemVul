__ecereNameSpace__ecere__UnloadTranslatedStrings(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__MapIterator it = (it.container = (void *)0, it.pointer = (void *)0, __ecereProp___ecereNameSpace__ecere__com__MapIterator_Set_map(&it, __ecereNameSpace__ecere__moduleMaps), it);

if(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Index(&it, (uint64)(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 12)))->name), 0x0))
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&it))->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&it)));
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__IteratorPointer * i))__ecereNameSpace__ecere__moduleMaps->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Delete])(__ecereNameSpace__ecere__moduleMaps, it.pointer);
}
}
