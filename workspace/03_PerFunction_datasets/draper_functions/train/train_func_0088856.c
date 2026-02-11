to_8bit_ascii(const FXString & input,const FXString & forbidden,FXuint opts) {
  FXString result;


  result = filter(input,forbidden,opts);


#if FOXVERSION < FXVERSION(1,7,29)
  result = compose(result,DecCompat);
#else
  result = compose(result,DecomposeCompat);
#endif


  result = convert_and_decompose(result);


  return result;
  }
