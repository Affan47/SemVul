__ecereInstMeth___ecereNameSpace__ecere__gui__controls__DataBox_NotifyChanged__00000006(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * dataBox, unsigned int closingDropDown)
{
struct __ecereNameSpace__ecere__gui__controls__CalendarControl * __ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl = (struct __ecereNameSpace__ecere__gui__controls__CalendarControl *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__CalendarControl->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->shownYear < 100)
{
int __simpleStruct0;
struct __ecereNameSpace__ecere__sys__DateTime time;

__ecereMethod___ecereNameSpace__ecere__sys__DateTime_GetLocalTime(&time);
__ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->shownYear += (time.year / 100) * 100;
if((__simpleStruct0 = __ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->shownYear - time.year, (__simpleStruct0 < 0) ? -__simpleStruct0 : __simpleStruct0) >= 50)
__ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->shownYear -= 100;
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_Refresh(__ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->yearBox);
}
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Activate(__ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl->dateBox);
return 0x1;
}
