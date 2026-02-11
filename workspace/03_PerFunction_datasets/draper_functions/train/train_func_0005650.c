ToString(double numberToConvert,
                     int digitsAfterDecimalPoint )
{
   wxString result = ToDisplayString(
      numberToConvert, digitsAfterDecimalPoint);

   result.Replace(wxString(GetDecimalSeparator()), wxT("."));

   return result;
}
