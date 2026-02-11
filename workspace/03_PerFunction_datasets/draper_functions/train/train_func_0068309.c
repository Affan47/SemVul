__ecereProp_IDEWorkSpace_Get_project(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

return __ecerePointer_IDEWorkSpace->projectView ? ((struct ProjectView *)(((char *)__ecerePointer_IDEWorkSpace->projectView + __ecereClass_ProjectView->offset)))->project : (((void *)0));
}
