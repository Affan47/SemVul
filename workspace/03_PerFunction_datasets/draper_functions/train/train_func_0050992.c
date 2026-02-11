GetFactory()
{
  if ( m_Factory == ITK_NULLPTR )
    {

    Pointer p = New();
    m_Factory = p.GetPointer();
    ObjectFactoryBase::RegisterFactory (p);
    p->RegisterDefaultTransforms ();
    }
  return m_Factory;
}
