FindParamsMemberInit(struct MemberInit * init, int line, int charPos)
{
struct Identifier * idResult;

if(init->initializer && InsideIncl(&init->initializer->loc, line, charPos))
{
idResult = FindParamsInitializer(init->initializer, line, charPos);
if(idResult)
{
if(init->identifiers && (*init->identifiers).first)
isAfterEqual = 0x1;
return idResult;
}
}
if(init->identifiers && (*init->identifiers).first && InsideIncl(&((struct Identifier *)(*init->identifiers).first)->loc, line, charPos))
{
idResult = FindParamsIdentifier((*init->identifiers).first, line, charPos);
if(idResult)
return idResult;
}
if(init->initializer && Inside(&init->initializer->loc, line, charPos))
{
if(init->identifiers && (*init->identifiers).first)
isAfterEqual = 0x1;
if(init->initializer->type == 0)
{
paramsInsideExp = init->initializer->exp;
return (void *)-1;
}
}
return (((void *)0));
}
