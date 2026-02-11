__ecereNameSpace__ecere__com__OnUnserialize(struct __ecereNameSpace__ecere__com__Class * _class, void ** data, struct __ecereNameSpace__ecere__com__Instance * channel)
{
struct __ecereNameSpace__ecere__com__Instance * module = _class->module;

if(_class->type == 3 || _class->type == 2 || _class->type == 4)
{
struct __ecereNameSpace__ecere__com__Class * dataType = __ecereNameSpace__ecere__com__eSystem_FindClass(module, _class->dataTypeString);

if(dataType)
((void (*)(void *, void *, void *))(void *)dataType->_vTbl[__ecereVMethodID_class_OnUnserialize])(dataType, data, channel);
}
else if(_class->type == 0 || _class->type == 5 || _class->type == 1)
{
if(data)
{
struct __ecereNameSpace__ecere__com__Class * lastClass = (((void *)0));

if(_class->type == 0 || _class->type == 5)
{
data = *data = __ecereNameSpace__ecere__com__eInstance_New(_class);
if(_class->type == 0)
((struct __ecereNameSpace__ecere__com__Instance *)(char *)((struct __ecereNameSpace__ecere__com__Instance *)data))->_refCount++;
}
else if(_class->type == 1)
memset(data, 0, _class->structSize);
while(lastClass != _class)
{
struct __ecereNameSpace__ecere__com__DataMember * member;
struct __ecereNameSpace__ecere__com__Class * c;

for(c = _class; c && (!c->base || c->base->type != 1000) && c->base != lastClass; c = c->base)
;
lastClass = c;
for(member = c->membersAndProperties.first; member; member = member->next)
{
if(member->id < 0)
continue;
if(member->isProperty || member->type == 0)
{
struct __ecereNameSpace__ecere__com__Class * memberType = member->dataTypeClass;

if(!memberType)
memberType = member->dataTypeClass = __ecereNameSpace__ecere__com__eSystem_FindClass(module, member->dataTypeString);
if(memberType)
{
if(member->isProperty)
{
}
else
((void (*)(void *, void *, void *))(void *)memberType->_vTbl[__ecereVMethodID_class_OnUnserialize])(memberType, (unsigned char *)data + (((member->_class->type == 0) ? member->_class->offset : 0) + member->offset), channel);
}
else
{
}
}
else
{
__ecereNameSpace__ecere__com__DataMember_OnUnserialize(member, (unsigned char *)data + (((member->_class->type == 0) ? member->_class->offset : 0) + member->offset), channel);
}
}
}
}
}
}
