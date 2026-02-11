__ecereMethod___ecereNameSpace__ecere__gui__controls__StatusBar_OnResizing(struct __ecereNameSpace__ecere__com__Instance * this, int * w, int * h)
{
int __simpleStruct0;
struct __ecereNameSpace__ecere__gui__controls__StatusBar * __ecerePointer___ecereNameSpace__ecere__gui__controls__StatusBar = (struct __ecereNameSpace__ecere__gui__controls__StatusBar *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__StatusBar->offset) : 0);

*h = (__simpleStruct0 = *h, (__simpleStruct0 > (18)) ? __simpleStruct0 : (18));
if(!*w)
*w = 80;
return 0x1;
}
