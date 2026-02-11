convert_to FCN((type,v0,v1))
TYPE type C0("Type to be converted to.")
VAL HUGE*v0 C0("Left-hand value.")
VAL HUGE*v1 C1("Right-hand value.")
{
switch(type)
{
case Int:break;

case Double:
TO_DOUBLE(v0);
TO_DOUBLE(v1);
break;

case Id:
TO_ID(v0);
TO_ID(v1);
break;

default:

{
if(eval_msgs)
macro_err(OC("! Invalid data type %s in promotion"),NO,stype(type));longjmp(top_of_evaluate,1);
}
}
}
