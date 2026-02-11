callAsFunction(ExecState *exec, JSObject *thisObj, const List &args)
{
  KJS_CHECK_THIS( KJS::HTMLSelectCollection, thisObj );
  DOM::HTMLSelectElementImpl* element = static_cast<KJS::HTMLSelectCollection *>(thisObj)->toElement();

  switch (id) {
  case KJS::HTMLSelectCollection::Add:
  {


    DOM::NodeImpl* node = KJS::toNode(args[0]);
    if (!node || node->id() != ID_OPTION)
      return throwError(exec, GeneralError, "Invalid argument to HTMLOptionsCollection::add");

    DOM::HTMLOptionElementImpl* option = static_cast<DOM::HTMLOptionElementImpl*>(node);

    int  pos = 0;

    if (args[1]->isUndefined())
      pos = element->length();
    else
      pos = (int)args[1]->toNumber(exec);

    if (pos < 0)
      return throwError(exec, GeneralError, "Invalid index argument to HTMLOptionsCollection::add");

    DOMExceptionTranslator exception(exec);
    if (pos >= element->length()) {

      element->add(option, 0, exception);
    } else {

      QVector<HTMLGenericFormElementImpl*> items = element->listItems();
      int dummy;
      element->insertBefore(option, items.at(pos), dummy);
    }
    return jsUndefined();
    break;
  }
  case KJS::HTMLSelectCollection::Remove:
  {
    double index;
    if (!args[0]->getNumber(index))
      index = 0;
    else {
      if (static_cast<long int>(index) >= element->length())
        index = 0;
    }
    element->remove(static_cast<long int>(index));
    return jsUndefined();
    break;
  }
  default:
    break;
  }
  return jsUndefined();
}
