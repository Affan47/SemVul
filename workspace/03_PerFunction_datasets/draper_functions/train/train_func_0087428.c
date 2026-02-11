setPatternForCurrencySpacing(UCurrencySpacing type,
                                                   UBool beforeCurrency,
                                             const UnicodeString& pattern) {
  if (beforeCurrency) {
    currencySpcBeforeSym[(int32_t)type] = pattern;
  } else {
    currencySpcAfterSym[(int32_t)type] =  pattern;
  }
}
