yearType(int32_t year) const
{
    int32_t yearLength = handleGetYearLength(year);

    if (yearLength > 380) {
        yearLength -= 30;
    }

    int type = 0;

    switch (yearLength) {
  case 353:
      type = 0; break;
  case 354:
      type = 1; break;
  case 355:
      type = 2; break;
  default:

      type = 1;
    }
    return type;
}
