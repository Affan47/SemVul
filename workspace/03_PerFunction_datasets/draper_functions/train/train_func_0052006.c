details() const
{
  std::string details;
  for ( Details::const_iterator it = m_details.begin(); it != m_details.end(); ++it )
  {
    details += "- ";
    details += *it;
    details += '\n';
  }
  return details;
}
