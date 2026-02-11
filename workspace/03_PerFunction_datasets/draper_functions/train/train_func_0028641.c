__ecereMethod_PathOptionBox_RetrieveOption(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * options, unsigned int isCfgOrPlt)
{
char ** string = (char **)((unsigned char *)options + ((struct OptionBox *)(((char *)this + __ecereClass_OptionBox->offset)))->option);
char * slashPath = __ecereProp___ecereNameSpace__ecere__gui__controls__PathBox_Get_slashPath(((struct __ecereNameSpace__ecere__com__Instance *)((struct OptionBox *)(((char *)this + __ecereClass_OptionBox->offset)))->editor));

if(*string)
(__ecereNameSpace__ecere__com__eSystem_Delete(*string), *string = 0);
*string = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(slashPath);
}
