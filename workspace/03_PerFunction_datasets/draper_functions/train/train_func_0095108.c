evaluateToInt(Expression *expr)
{
  gint64 value = 0;

  try {
    if(expr) {

      Value *v = expr->evaluate();

      v->get(value);

      delete v;
      delete expr;
    }

  }

  catch (Error *err) {
    if(err)
      cout << "ERROR:" << err->toString() << endl;
    delete err;
  }

  return value;
}
