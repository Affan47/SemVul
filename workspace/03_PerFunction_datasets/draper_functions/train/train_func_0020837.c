PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "CompressionLevel: " << m_CompressionLevel << std::endl;
  if ( m_IsReadAsScalarPlusPalette )
    {
    os << "Read as Scalar Image plus palette" << "\n";
    }
  if( m_ColorPalette.size() > 0  )
    {
    os << indent << "ColorPalette:" << std::endl;
    for( unsigned int i = 0; i < m_ColorPalette.size(); ++i )
      {
      os << indent << "[" << i << "]"
         << itk::NumericTraits< PaletteType::value_type >::PrintType( m_ColorPalette[i] ) << std::endl;
      }
    }
}
