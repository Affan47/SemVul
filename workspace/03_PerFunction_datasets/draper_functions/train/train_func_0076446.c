GetMathFunctionNumberByCheckingParenthesis
  ( int currentIndex )
{


  const  int  NUMBFUNCS                =  24;

  static int  charsLens[NUMBFUNCS]     = { 4,       4,        5,       6,
                                           3,       6,        4,       5,
                                           4,       5,        4,       5,
                                           4,       5,        5,       5,
                                           5,       4,        4,       6,
                                           5,       4,        5,       3
                                         };

  static int  funcNumbs[NUMBFUNCS]     = { VTK_PARSER_ABSOLUTE_VALUE,
                                           VTK_PARSER_EXPONENT,
                                           VTK_PARSER_CEILING,
                                           VTK_PARSER_FLOOR,

                                           VTK_PARSER_LOGARITHME,
                                           VTK_PARSER_LOGARITHM10,
                                           VTK_PARSER_LOGARITHM,
                                           VTK_PARSER_SQUARE_ROOT,

                                           VTK_PARSER_SINE,
                                           VTK_PARSER_HYPERBOLIC_SINE,
                                           VTK_PARSER_COSINE,
                                           VTK_PARSER_HYPERBOLIC_COSINE,

                                           VTK_PARSER_TANGENT,
                                           VTK_PARSER_HYPERBOLIC_TANGENT,
                                           VTK_PARSER_ARCSINE,
                                           VTK_PARSER_ARCCOSINE,

                                           VTK_PARSER_ARCTANGENT,
                                           VTK_PARSER_MIN,
                                           VTK_PARSER_MAX,
                                           VTK_PARSER_CROSS,

                                           VTK_PARSER_SIGN,
                                           VTK_PARSER_MAGNITUDE,
                                           VTK_PARSER_NORMALIZE,
                                           VTK_PARSER_IF
                                         };

  static char funcNames[NUMBFUNCS][10] = { "abs(",  "exp(",   "ceil(", "floor(",
                                           "ln(",   "log10(", "log(",  "sqrt(",
                                           "sin(",  "sinh(",  "cos(",  "cosh(",
                                           "tan(",  "tanh(",  "asin(", "acos(",
                                           "atan(", "min(",   "max(",  "cross(",
                                           "sign(", "mag(",   "norm(", "if("
                                         };

  int   isMatched = 0;
  int   retNumber = 0;
  for ( int i = 0; i < NUMBFUNCS && isMatched == 0; i ++ )
    {
    isMatched = (  strncmp( this->Function + currentIndex,
                            funcNames[i], charsLens[i]
                          ) == 0
                )  ?  1  :  0;
    retNumber = isMatched * funcNumbs[i];
    }

  return retNumber;
}
