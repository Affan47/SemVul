__ecereMethod___ecereNameSpace__eda__PrintedReport_EndPage(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * page)
{
struct __ecereNameSpace__eda__PrintedReport * __ecerePointer___ecereNameSpace__eda__PrintedReport = (struct __ecereNameSpace__eda__PrintedReport *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__PrintedReport->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
__ecereMethod___ecereNameSpace__ecere__gui__GuiApplication_ProcessInput(((struct __ecereNameSpace__ecere__com__Instance *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application), 0x1);
__ecereMethod___ecereNameSpace__ecere__gui__GuiApplication_UpdateDisplay(((struct __ecereNameSpace__ecere__com__Instance *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Destroy(__ecerePointer___ecereNameSpace__eda__PrintedReport->lastPage, 0);
}
