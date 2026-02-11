AcTan(double sinx, double cosx)
{
  if(cosx == 0)
    {
      if(sinx > 0)
	return (pio2);
      else
	return (x3pio2);
    }
  else
    {
      if(cosx > 0)
	{
	  if(sinx > 0)
	    return ( atan(sinx/cosx) );
	  else
	    return ( twopi + atan(sinx/cosx) );
	}
      else
	return ( pi + atan(sinx/cosx) );
    }

}
