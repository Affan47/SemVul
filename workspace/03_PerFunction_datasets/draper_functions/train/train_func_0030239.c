GetNumberOfIntegrationPoints(unsigned int order) const
{

  if( order == 0 || order > 5 )
    {
    order = DefaultIntegrationOrder;
    }

  return Nip[order];
}
