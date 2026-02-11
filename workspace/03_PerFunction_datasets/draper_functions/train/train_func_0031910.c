construct(ExecState *exec, const List &args)
{
  DOMExceptionTranslator exception(exec);
  DOM::ElementImpl* el = doc->createElement("OPTION");
  DOM::HTMLOptionElementImpl* opt = static_cast<DOM::HTMLOptionElementImpl*>(el);
  int sz = args.size();
  SharedPtr<DOM::TextImpl> t = doc->createTextNode("");

  int dummyexception = 0;
  opt->appendChild(t.get(), dummyexception);

  if (sz > 0)
    t->setData(args[0]->toString(exec).domString(), exception);
  if (sz > 1)
    opt->setValue(args[1]->toString(exec).domString().implementation());
  if (sz > 2)
    opt->setDefaultSelected(args[2]->toBoolean(exec));
  if (sz > 3)
    opt->setSelected(args[3]->toBoolean(exec));

  return getDOMNode(exec,opt)->getObject();
}
