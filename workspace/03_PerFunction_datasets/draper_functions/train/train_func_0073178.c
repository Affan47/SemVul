__ecereDestructor___ecereNameSpace__ecere__gui__controls__OldArray(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__OldArray * __ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray = (struct __ecereNameSpace__ecere__gui__controls__OldArray *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__OldArray->offset) : 0);

{
int c;
void ** array = (void **)((struct __ecereNameSpace__ecere__gui__controls__ArrayImpl *)(((char *)((struct __ecereNameSpace__ecere__com__Instance *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ArrayImpl->offset)))->array;

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray->type->type == 0 || __ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray->type->type == 5)
{
for(c = 0; c < __ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray->size; c++)
((void (*)(void *, void *))(void *)__ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray->type->_vTbl[__ecereVMethodID_class_OnFree])(__ecerePointer___ecereNameSpace__ecere__gui__controls__OldArray->type, array[c]);
}
(__ecereNameSpace__ecere__com__eSystem_Delete(((struct __ecereNameSpace__ecere__gui__controls__ArrayImpl *)(((char *)((struct __ecereNameSpace__ecere__com__Instance *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ArrayImpl->offset)))->array), ((struct __ecereNameSpace__ecere__gui__controls__ArrayImpl * )(((char * )((struct __ecereNameSpace__ecere__com__Instance *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ArrayImpl->offset)))->array = 0);
}
}
