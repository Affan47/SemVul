__ecereConstructor___ecereNameSpace__eda__PrintedReport(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__PrintedReport * __ecerePointer___ecereNameSpace__eda__PrintedReport = (struct __ecereNameSpace__eda__PrintedReport *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__PrintedReport->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_displayDriver(this, "Win32Printer");
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_fullRender(this, 0x1);
return 0x1;
}
