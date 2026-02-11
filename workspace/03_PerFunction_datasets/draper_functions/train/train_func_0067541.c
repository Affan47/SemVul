getJSLazyEventListener(const QString& code, const QString& srcUrl, int line,
                                                    const QString& name, DOM::NodeImpl *node, bool svg)
{
  return new JSLazyEventListener(code, srcUrl, line, name, this, node, svg);
}
