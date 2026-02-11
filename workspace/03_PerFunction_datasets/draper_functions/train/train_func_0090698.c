scale (double value)
  {
    makeThisCurrent();
    if (checkImgDataTypeChange(zero(), value))
    {
       if (naxis())
       {
           int status(0);
           if (fits_update_key(fitsPointer(), Tdouble, BSCALE, &value, 0, &status))
              throw FitsError(status);
           fits_flush_file(fitsPointer(), &status);
           HDU::scale(value);
       }
    }
    else
    {
       bool silent=false;
       string msg("CCfits Error: Cannot set BSCALE to a value which will change image data\n");
           msg += "              from integer type to floating point type.";
       throw FitsException(msg,silent);
    }
  }
