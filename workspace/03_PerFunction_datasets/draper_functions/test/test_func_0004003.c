SetupBaseSpecs(struct Symbol * symbol, struct __ecereNameSpace__ecere__sys__OldList * baseSpecs)
{
if(baseSpecs && baseSpecs->first && ((struct Specifier *)baseSpecs->first)->type == 1)
{
char name[1024];
struct Symbol * baseClass;
char * tpl;

strcpy(name, ((struct Specifier *)baseSpecs->first)->name);
tpl = strchr(name, '<');
if(tpl)
*tpl = (char)0;
baseClass = FindClass(name);
if(baseClass && baseClass->ctx)
{
struct TemplatedType * copy;

for(copy = (struct TemplatedType *)__ecereProp___ecereNameSpace__ecere__sys__BinaryTree_Get_first(&baseClass->ctx->templateTypes); copy; copy = (struct TemplatedType *)__ecereProp___ecereNameSpace__ecere__sys__BTNode_Get_next(copy))
{
struct TemplatedType * type = (type = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_TemplatedType), type->key = copy->key, type->param = copy->param, type);

if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&curContext->templateTypes, (struct __ecereNameSpace__ecere__sys__BTNode *)type))
((type ? (__ecereClass_TemplatedType->Destructor ? __ecereClass_TemplatedType->Destructor(type) : 0, __ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor(type) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(type)) : 0), type = 0);
}
}
else if(baseClass && baseClass->registered)
{
struct __ecereNameSpace__ecere__com__Class * sClass;

for(sClass = baseClass->registered; sClass; sClass = sClass->base)
{
struct __ecereNameSpace__ecere__com__ClassTemplateParameter * p;

for(p = sClass->templateParams.first; p; p = p->next)
{
if(p->type == 0)
{
struct TemplateParameter * param = p->param;
struct TemplatedType * type;

if(!param)
{
p->param = param = __extension__ ({
struct TemplateParameter * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_TemplateParameter);

__ecereInstance1->identifier = MkIdentifier(p->name), __ecereInstance1->type = p->type, __ecereInstance1->dataTypeString = p->dataTypeString, __ecereInstance1;
});
}
type = __extension__ ({
struct TemplatedType * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_TemplatedType);

__ecereInstance1->key = (uintptr_t)p->name, __ecereInstance1->param = param, __ecereInstance1;
});
if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&curContext->templateTypes, (struct __ecereNameSpace__ecere__sys__BTNode *)type))
((type ? (__ecereClass_TemplatedType->Destructor ? __ecereClass_TemplatedType->Destructor(type) : 0, __ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor(type) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(type)) : 0), type = 0);
}
}
}
}
}
}
