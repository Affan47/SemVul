__ecereMethod_Project_MatchProjectAndConfigPlatformOptions(struct Project * this, struct ProjectConfig * config, int platform, struct __ecereNameSpace__ecere__com__Instance ** projectPlatformOptions, struct __ecereNameSpace__ecere__com__Instance ** configPlatformOptions)
{
*projectPlatformOptions = (((void *)0));
*configPlatformOptions = (((void *)0));
if(this->platforms)
{
{
struct __ecereNameSpace__ecere__com__Instance ** p;
struct __ecereNameSpace__ecere__com__Instance * __internalArray = this->platforms;

for(p = (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array; p < (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array + ((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->count; p++)
{
if(!(strcasecmp)(__extension__ ({
char * __ecTemp1 = ((*p));

((struct PlatformOptions *)(__ecTemp1 + __ecereClass_PlatformOptions->offset));
})->name, __ecereProp___ecereNameSpace__ecere__com__Platform_Get_char__PTR_(platform)))
{
*projectPlatformOptions = (*p);
break;
}
}
}
}
if(config && __ecereProp_ProjectConfig_Get_platforms(config))
{
{
struct __ecereNameSpace__ecere__com__Instance ** p;
struct __ecereNameSpace__ecere__com__Instance * __internalArray = __ecereProp_ProjectConfig_Get_platforms(config);

for(p = (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array; p < (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array + ((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->count; p++)
{
if(!(strcasecmp)(__extension__ ({
char * __ecTemp1 = ((*p));

((struct PlatformOptions *)(__ecTemp1 + __ecereClass_PlatformOptions->offset));
})->name, __ecereProp___ecereNameSpace__ecere__com__Platform_Get_char__PTR_(platform)))
{
*configPlatformOptions = (*p);
break;
}
}
}
}
}
