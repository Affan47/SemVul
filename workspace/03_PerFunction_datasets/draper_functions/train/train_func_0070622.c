pTopViewBar() const
{
  if (const_cast<KHTMLPart*>(this)->parentPart())
      return const_cast<KHTMLPart*>(this)->parentPart()->pTopViewBar();
  return d->m_topViewBar;
}
