setDOMException(ExecState *exec, int internalCode)
{
  if (internalCode == 0 || exec->hadException())
    return;

  const char* type = 0;

  DOMString name;
  DOMString exceptionString;
  JSObject* errorObject = 0;
  int code = -1;


  if (DOM::RangeException::isRangeExceptionCode(internalCode)) {
    type = "DOM Range";
    code = internalCode - DOM::RangeException::_EXCEPTION_OFFSET;
    name = DOM::RangeException::codeAsString(code);
    errorObject = new RangeException(exec);
  } else if (DOM::CSSException::isCSSExceptionCode(internalCode)) {
    type = "CSS";
    code = internalCode - DOM::CSSException::_EXCEPTION_OFFSET;
    name = DOM::CSSException::codeAsString(code);
  } else if (DOM::EventException::isEventExceptionCode(internalCode)) {
    type = "DOM Events";
    code = internalCode - DOM::EventException::_EXCEPTION_OFFSET;
    name = DOM::EventException::codeAsString(code);
  } else if (DOM::XPathException::isXPathExceptionCode(internalCode)) {
    type = "XPath";
    code = internalCode - DOM::XPathException::_EXCEPTION_OFFSET;
    name = DOM::XPathException::codeAsString(code);
  } else {

    type = "DOM";
    code = internalCode;
    name = DOM::DOMException::codeAsString(code);
    errorObject = new JSDOMException(exec);
  }

  if (!errorObject) {


    char buffer[100];

    if (!name.isEmpty())
      snprintf(buffer, 99, "%s: %s Exception %d", name.string().toLatin1().data(), type, code);
    else
      snprintf(buffer, 99, "%s Exception %d", type, code);
    errorObject = throwError(exec, GeneralError, buffer);
  } else {
    exec->setException(errorObject);
  }

  errorObject->put(exec, exec->propertyNames().name, jsString(UString(type) + " Exception"));
  errorObject->put(exec, exec->propertyNames().message, jsString(name));
  errorObject->put(exec, "code", jsNumber(code));
}
