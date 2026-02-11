__ecereMethod___ecereNameSpace__ecere__com__Array_SetData(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__IteratorPointer * ip, uint64 value)
{
struct __ecereNameSpace__ecere__com__Array * __ecerePointer___ecereNameSpace__ecere__com__Array = (struct __ecereNameSpace__ecere__com__Array *)(this ? (((char *)this) + 24) : 0);
uint64 * item = (uint64 *)ip;

(memcpy(item, (char *)(((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 1) ? value : ((char *)&value + __ENDIAN_PAD((((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 1 || ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 0 || ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 5) ? sizeof(void *) : ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->typeSize)), (((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 0 || ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->type == 5) ? sizeof(void *) : ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[0].dataTypeClass->typeSize));
return 0x1;
}
