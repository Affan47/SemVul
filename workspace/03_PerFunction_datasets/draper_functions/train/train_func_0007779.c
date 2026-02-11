__ecereMethod___ecereNameSpace__ecere__gui__controls__DropBox_OnResizing(struct __ecereNameSpace__ecere__com__Instance * this, int * width, int * height)
{
int __simpleStruct2, __simpleStruct3;
int __simpleStruct0, __simpleStruct1;
struct __ecereNameSpace__ecere__gui__controls__DropBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox = (struct __ecereNameSpace__ecere__gui__controls__DropBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DropBox->offset) : 0);
int rowHeight = 0;

__ecereMethod___ecereNameSpace__ecere__gfx__Display_FontExtent(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_display(this), __ecereProp___ecereNameSpace__ecere__gui__Window_Get_fontObject(this), "W", 1, (((void *)0)), &rowHeight);
rowHeight = ((rowHeight > 16) ? rowHeight : 16);
if(!*width)
*width = (__simpleStruct0 = *width, __simpleStruct1 = rowHeight * 100 / 16, (__simpleStruct0 > __simpleStruct1) ? __simpleStruct0 : __simpleStruct1);
if(!*height)
*height = (__simpleStruct2 = *height, __simpleStruct3 = rowHeight * 20 / 16, (__simpleStruct2 > __simpleStruct3) ? __simpleStruct2 : __simpleStruct3);
return 0x1;
}
