operator<< <float> (std::ostream & os, const Array2D< float > & arr)
{
  NumberToString<float> convert;
  const unsigned int numberOfRows    = arr.rows();
  const unsigned int numberOfColumns = arr.cols();

  for ( unsigned int r = 0; r < numberOfRows; ++r )
    {
    os << "[";
    if ( numberOfColumns >= 1 )
      {
      const unsigned int lastColumn = numberOfColumns - 1;
      for ( unsigned int c = 0; c < lastColumn; ++c )
        {
        os << convert(arr(r, c)) << ", ";
        }
      os << convert(arr(r, lastColumn));
      }
    os << "]" << std::endl;
    }

  return os;
}
