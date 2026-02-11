vector_width() const
{
      if (msb_ > lsb_)
	    return msb_ - lsb_ + 1;
      else
	    return lsb_ - msb_ + 1;
}
