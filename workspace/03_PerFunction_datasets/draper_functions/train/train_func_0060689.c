__ecereMethod___ecereNameSpace__ecere__gui__FormDesigner_FixProperty(struct __ecereNameSpace__ecere__com__Property * prop, struct __ecereNameSpace__ecere__com__Instance * object)
{
struct __ecereNameSpace__ecere__com__Instance * designer = (struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__DesignerBase_Get_classDesigner(__ecereNameSpace__ecere__com__activeDesigner);

if(!strcmp(prop->name, "parent"))
{
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(object) == __ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Get_desktop(__ecereNameSpace__ecere__gui__guiApp))
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(object, ((struct __ecereNameSpace__ecere__gui__FormDesigner *)(((char *)designer + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset)))->form);
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(object) == ((struct __ecereNameSpace__ecere__gui__FormDesigner *)(((char *)designer + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset)))->form)
{
struct __ecereNameSpace__ecere__com__ObjectInfo * previous = ((struct __ecereNameSpace__ecere__gui__Window *)(((char *)object + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->object;

while((previous = previous->prev) && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(((struct __ecereNameSpace__ecere__com__Instance *)previous->instance)) != ((struct __ecereNameSpace__ecere__gui__FormDesigner *)(((char *)designer + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset)))->form)
;
if(previous)
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Move(&__extension__ ({
char * __ecTemp1 = (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(object));

((struct __ecereNameSpace__ecere__gui__Window *)(__ecTemp1 + __ecereClass___ecereNameSpace__ecere__gui__Window->offset));
})->children, object, (struct __ecereNameSpace__ecere__com__Instance *)previous->instance);
}
}
if(!strcmp(prop->name, "master") && !__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(object))
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(object, ((struct __ecereNameSpace__ecere__gui__FormDesigner *)(((char *)designer + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset)))->form);
if(!strcmp(prop->name, "visible"))
{
((struct __ecereNameSpace__ecere__gui__Window *)(((char *)object + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->setVisible = !((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)object + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x40) >> 6));
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_visible(object, 0x1);
}
}
