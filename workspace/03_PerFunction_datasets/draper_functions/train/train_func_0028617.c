evaluate()
{
  Value* tmp, *vReturn;


  tmp = expr->evaluate();


  vReturn = applyOp(tmp);


  delete tmp;
  return vReturn;
}
