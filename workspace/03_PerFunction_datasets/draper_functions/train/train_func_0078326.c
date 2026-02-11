GetMaximum(
         int* success)
{
  double result;
  int isValid;

  switch(d_dataset->cellRepresentation()) {
    case CR_UINT1: {
      UINT1 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    case CR_INT4: {
      INT4 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    case CR_REAL4: {
      REAL4 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }

    case CR_INT1: {
      INT1 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    case CR_INT2: {
      INT2 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    case CR_UINT2: {
      UINT2 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    case CR_UINT4: {
      UINT4 max;
      isValid = RgetMaxVal(d_dataset->map(), &max);
      result = static_cast<double>(max);
      break;
    }
    default: {
      result = 0.0;
      isValid = 0;
      break;
    }
  }

  if(success) {
    *success = isValid ? 1 : 0;
  }

  return result;
}
