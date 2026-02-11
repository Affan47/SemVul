PrintArray(MeasureType *array)
{
  for ( int i = 0; i < (int)( array->GetNumberOfElements() ); i++ )
    {
    std::cerr << i << " " << array->get(i) << std::endl;
    }
}
