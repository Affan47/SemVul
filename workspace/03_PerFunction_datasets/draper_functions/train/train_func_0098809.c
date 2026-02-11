__ecereMethod_ToolBox_OnKeyDown(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int key, unsigned int ch)
{
struct ToolBox * __ecerePointer_ToolBox = (struct ToolBox *)(this ? (((char *)this) + __ecereClass_ToolBox->offset) : 0);

if(key == 0x1)
{
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace))
__ecereMethod___ecereNameSpace__ecere__gui__Window_Activate(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace));
}
return 0x1;
}
