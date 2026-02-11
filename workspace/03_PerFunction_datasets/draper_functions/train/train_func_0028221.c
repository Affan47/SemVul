__ecereMethod___ecereNameSpace__eda__StringList_Delete(struct __ecereNameSpace__ecere__com__Instance * this, char * string)
{
struct __ecereNameSpace__eda__StringList * __ecerePointer___ecereNameSpace__eda__StringList = (struct __ecereNameSpace__eda__StringList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__StringList->offset) : 0);
struct __ecereNameSpace__ecere__sys__BTNode * node = __ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&__ecerePointer___ecereNameSpace__eda__StringList->strings, string);

if(node)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Delete(&__ecerePointer___ecereNameSpace__eda__StringList->strings, node);
return 0x1;
}
return 0x0;
}
