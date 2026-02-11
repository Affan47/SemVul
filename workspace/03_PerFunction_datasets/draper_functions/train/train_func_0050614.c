FreeAsmField(struct AsmField * field)
{
if(field->expression)
FreeExpression(field->expression);
(__ecereNameSpace__ecere__com__eSystem_Delete(field->command), field->command = 0);
((field ? (__ecereClass_AsmField->Destructor ? __ecereClass_AsmField->Destructor(field) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(field)) : 0), field = 0);
}
