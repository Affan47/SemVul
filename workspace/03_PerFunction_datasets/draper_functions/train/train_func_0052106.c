invresolsq_range() const
{
  Range<ftype> slim;
  HKL_info::HKL_reference_index ih;
  for ( ih = first_data(); !ih.last(); next_data(ih) )
    slim.include( invresolsq( ih.index() ) );
  return slim;
}
