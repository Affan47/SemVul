__ecereMethod_IDEWorkSpace_PictureEditOnClose(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int parentClosing)
{
struct PictureEdit * __ecerePointer_PictureEdit = (struct PictureEdit *)(this ? (((char *)this) + __ecereClass_PictureEdit->offset) : 0);

if(!parentClosing && __ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace))
__ecereMethod_Workspace_UpdateOpenedFileInfo(__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace), __ecerePointer_PictureEdit->fileName, 0);
return 0x1;
}
