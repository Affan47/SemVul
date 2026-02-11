__ecereMethod___ecereNameSpace__ecere__gfx__DisplaySystem_AddTexture(struct __ecereNameSpace__ecere__com__Instance * this, char * name, struct __ecereNameSpace__ecere__com__Instance * bitmap)
{
struct __ecereNameSpace__ecere__gfx__DisplaySystem * __ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem = (struct __ecereNameSpace__ecere__gfx__DisplaySystem *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__DisplaySystem->offset) : 0);
struct __ecereNameSpace__ecere__sys__NamedLink * item = __ecereNameSpace__ecere__com__eSystem_New0(32);

if(item)
{
item->data = bitmap;
item->name = __ecereNameSpace__ecere__com__eSystem_New(sizeof(char) * (strlen(name) + 1));
strcpy(item->name, name);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_AddName(&__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->textures, item);
}
return item;
}
