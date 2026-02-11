labelAlignment(MSAlignment alignment_)
{
  if (alignment_!=labelAlignment())
   {
     if (alignment_==MSLeft||alignment_==MSTop)
      {
	_labelAlignment=alignment_;
	computeSize();
      }
   }
}
