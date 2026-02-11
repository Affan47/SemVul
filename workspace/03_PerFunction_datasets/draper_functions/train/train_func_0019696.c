__ecereNameSpace__ecere__sys__GetFileEntries(struct __ecereNameSpace__ecere__sys__OldList * list, char * path)
{
struct __ecereNameSpace__ecere__sys__FileListing listing =
{
path, (((void * )0)), 0
};

while(__ecereMethod___ecereNameSpace__ecere__sys__FileListing_Find(&listing))
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(list, __extension__ ({
struct __ecereNameSpace__ecere__sys__FileStats __simpleStruct2;
struct __ecereNameSpace__ecere__sys__FileStats __simpleStruct1;
struct __ecereNameSpace__ecere__sys__FileStats __simpleStruct0;
struct __ecereNameSpace__ecere__sys__FileEntry * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__sys__FileEntry);

__ecereInstance1->name = __ecereNameSpace__ecere__sys__CopyString(__ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_name(&listing)), (__ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_stats(&listing, &__simpleStruct0), __ecereInstance1->attribs = __simpleStruct0.attribs), (__ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_stats(&listing, &__simpleStruct1), __ecereInstance1->modified = __simpleStruct1.modified), (__ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_stats(&listing, &__simpleStruct2), __ecereInstance1->size = __simpleStruct2.size), __ecereInstance1;
}));
}
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Sort(list, __ecereNameSpace__ecere__sys__CompareFiles, (((void *)0)));
}
