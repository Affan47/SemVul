isIdentPartLibC(int c)
{
  return (category(c) & (Letter_Uppercase | Letter_Lowercase |
			 Letter_Titlecase | Letter_Modifier | Letter_Other |
			 Mark_NonSpacing | Mark_SpacingCombining |
			 Number_DecimalDigit | Punctuation_Connector))
    || c == '$' || c == '_';
}
