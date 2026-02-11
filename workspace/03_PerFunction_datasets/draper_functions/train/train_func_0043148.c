Make()
{
  switch ( histogramType_ )
  {
    case 1:
      MakeHorizontalHistogramNoTails();
      break;
    case 2:
      MakeHorizontalHistogramWithTails();
      break;
    case 3:
      MakeVerticalHistogramNoTails();
      break;
    case 4:
      MakeVerticalHistogramWithTails();
      break;
    default:
      MakeNonHistogram();
  }
  MakeErrorBars();
}
