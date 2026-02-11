PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "LearningRate: "
     << m_LearningRate << std::endl;
  os << indent << "NunberOfIterations: "
     << m_NumberOfIterations << std::endl;
  os << indent << "Maximize: "
     << m_Maximize << std::endl;
  os << indent << "CurrentIteration: "
     << m_CurrentIteration;
  os << indent << "Value: "
     << m_Value;
  if ( m_CostFunction )
    {
    os << indent << "CostFunction: "
       << m_CostFunction;
    }
  os << indent << "StopCondition: "
     << m_StopCondition;
  os << std::endl;
  os << indent << "Gradient: "
     << m_Gradient;
  os << std::endl;
}
