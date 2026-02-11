__ecereMethod_PathOptionBox_OptionCheck(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * options)
{
char * string = *(char **)((unsigned char *)options + ((struct OptionBox *)(((char *)this + __ecereClass_OptionBox->offset)))->option);

return string && string[0];
}
