__ecereNameSpace__ecere__com__eClass_AddDataMember(struct __ecereNameSpace__ecere__com__Class * _class, char * name, char * type, unsigned int size, unsigned int alignment, int declMode)
{
if(_class && name)
{
if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&_class->members, name))
{
struct __ecereNameSpace__ecere__com__DataMember * dataMember;

if(alignment)
{
int __simpleStruct0;

_class->structAlignment = (__simpleStruct0 = _class->structAlignment, (__simpleStruct0 > alignment) ? __simpleStruct0 : alignment);
if(_class->memberOffset % alignment)
_class->memberOffset += alignment - (_class->memberOffset % alignment);
}
dataMember = __extension__ ({
struct __ecereNameSpace__ecere__com__DataMember * __ecereInstance1 = __ecereNameSpace__ecere__com__eSystem_New0(160);

__ecereInstance1->name = __ecereNameSpace__ecere__sys__CopyString(name), __ecereInstance1->dataTypeString = __ecereNameSpace__ecere__sys__CopyString(type), __ecereInstance1->id = _class->memberID++, __ecereInstance1->_class = _class, __ecereInstance1->offset = _class->memberOffset, __ecereInstance1->memberOffset = size, __ecereInstance1->memberAccess = declMode, __ecereInstance1->membersAlpha.CompareKey = (void *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_CompareString, __ecereInstance1;
});
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&_class->membersAndProperties, dataMember);
_class->memberOffset += size;
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&_class->members, (struct __ecereNameSpace__ecere__sys__BTNode *)__extension__ ({
struct __ecereNameSpace__ecere__com__BTNamedLink * __ecereInstance1 = __ecereNameSpace__ecere__com__eSystem_New0(48);

__ecereInstance1->name = dataMember->name, __ecereInstance1->data = dataMember, __ecereInstance1;
}));
return dataMember;
}
}
return (((void *)0));
}
