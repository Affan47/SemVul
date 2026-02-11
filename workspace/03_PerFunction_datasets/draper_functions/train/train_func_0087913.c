set_stylehints(char fore, char back)
{
  glui32 n;
  for(n = 0; n < style_NUMSTYLES; n++)
    killglkwithcolor(n, fore, back);


  glk_stylehint_set(wintype_TextBuffer, style_Subheader,
		    stylehint_Weight, 1);


  glk_stylehint_set(wintype_TextBuffer, style_BlockQuote,
		    stylehint_Proportional, 0);
  glk_stylehint_set(wintype_TextBuffer, style_BlockQuote,
		    stylehint_Justification, stylehint_just_Centered);
#ifdef stylehint_ReverseColor
  glk_stylehint_set(wintype_TextBuffer, style_BlockQuote,
		    stylehint_ReverseColor, 1);
#endif


  glk_stylehint_set(wintype_TextBuffer, style_User1,
		    stylehint_Weight, 1);
  glk_stylehint_set(wintype_TextBuffer, style_User1,
		    stylehint_Oblique, 1);


  glk_stylehint_set(wintype_TextBuffer, style_User2,
		    stylehint_Proportional, 0);
  glk_stylehint_set(wintype_TextBuffer, style_User2,
		    stylehint_Weight, 1);
}
