postprocess()
{

  if (m_parent)
    QCoreApplication::postEvent(m_parent,
				new KReverseResolverEvent(node, service, success));
  return true;
}
