stopAnimations()
{
  if ( d->m_doc )
    d->m_doc->docLoader()->setShowAnimations( KHTMLSettings::KAnimationDisabled );

  ConstFrameIt it = d->m_frames.constBegin();
  const ConstFrameIt end = d->m_frames.constEnd();
  for (; it != end; ++it ) {
    if ( KHTMLPart* p = qobject_cast<KHTMLPart*>((*it)->m_part.data()) )
      p->stopAnimations();
  }
}
