PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  if ( m_CostFunction )
    {
    os << indent << "Cost Function: " << m_CostFunction.GetPointer() << std::endl;
    }
}
