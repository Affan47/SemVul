__ecereMethod___ecereNameSpace__eda__IdList_OnEdit(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * dataBox, struct __ecereNameSpace__ecere__com__Instance * obsolete, int x, int y, int w, int h, void * userData)
{
struct __ecereNameSpace__ecere__gui__Anchor __simpleStruct0 =
{

{
1, 0LL
},
{
1, 0LL
},
{
1, 0LL
},
{
1, 0LL
}
};
int __internalValue001;
struct __ecereNameSpace__eda__IdList * __ecerePointer___ecereNameSpace__eda__IdList = (struct __ecereNameSpace__eda__IdList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__IdList->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * list = (list = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__ListBox), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(list, dataBox), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_borderStyle(list, (unsigned int)0), __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Set_alwaysEdit(list, 0x1), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_anchor(list, &__simpleStruct0), __ecereNameSpace__ecere__com__eInstance_SetMethod(list, "NotifyChanged", __ecereInstMeth___ecereNameSpace__ecere__gui__controls__ListBox_NotifyChanged__00000002), list);
int c;
struct __ecereNameSpace__ecere__com__Instance * r;

{
struct __ecereNameSpace__ecere__com__Class * type = (*((struct __ecereClassData___ecereNameSpace__eda__IdList *)((char *)class->data + __ecereClass___ecereNameSpace__eda__IdList->offsetClass))).type;

__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_AddField(list, __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__DataField);

__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Set_dataType(__ecereInstance1, type), __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Set_editable(__ecereInstance1, 0x1), __ecereInstance1;
}));
}
for(c = 0; c < ((struct __ecereNameSpace__ecere__com__Instance *)this ? __ecerePointer___ecereNameSpace__eda__IdList->count : 0); c++)
{
r = __ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_AddRow(list);
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(r, (((void *)0)), &__ecerePointer___ecereNameSpace__eda__IdList->ids[c]);
}
r = __ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_AddRow(list);
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(r, (((void *)0)), __extension__ ({
__internalValue001 = 0;
&__internalValue001;
}));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Create(list);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(list, 0x0);
return list;
}
