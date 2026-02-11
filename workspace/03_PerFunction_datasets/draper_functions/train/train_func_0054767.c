__ecereNameSpace__ecere__com__eSystem_FindDefine(struct __ecereNameSpace__ecere__com__Instance * module, char * name)
{
if(name && module)
{
struct __ecereNameSpace__ecere__com__BTNamedLink * link;

link = __ecereNameSpace__ecere__com__SearchNameSpace(&((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application + 560)))->systemNameSpace, name, &(*((struct __ecereNameSpace__ecere__com__NameSpace *)0)).defines);
if(link)
return link->data;
link = __ecereNameSpace__ecere__com__SearchModule(module, name, &(*((struct __ecereNameSpace__ecere__com__NameSpace *)0)).defines, 0x1);
if(link)
return link->data;
}
return (((void *)0));
}
