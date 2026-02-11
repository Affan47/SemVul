generate_code()
{
  funcdecl *f = (funcdecl *) func->getvalue();
  return
    tsprintf("%s( %s )",
             func->getvalue()->generate_code(),
             actuals != NULL ?
             actuals->generate_code(func->getname()->getname(), f->params) : "");
}
