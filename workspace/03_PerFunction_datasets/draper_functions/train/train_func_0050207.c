ProcessFunction(struct FunctionDefinition * function)
{
if(function->body)
{
yylloc = function->loc;
ProcessStatement(function->body);
}
}
