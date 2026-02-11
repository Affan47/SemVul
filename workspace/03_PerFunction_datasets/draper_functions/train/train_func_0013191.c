putValueProperty(ExecState *exec, int token, JSValue *value, int)
{
  switch (token) {

  case Style_SelectorText:
    static_cast<CSSStyleRuleImpl *>(m_impl.get())->setSelectorText(value->toString(exec).domString());
    return;


  case Page_SelectorText:
    static_cast<CSSPageRuleImpl *>(m_impl.get())->setSelectorText(value->toString(exec).domString());
    return;


  case Charset_Encoding:
    static_cast<CSSCharsetRuleImpl *>(m_impl.get())->setEncoding(value->toString(exec).domString());
    return;

  default:
    kDebug(6070) << "DOMCSSRule::putValueProperty unhandled token " << token;
  }
}
