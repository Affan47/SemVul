applyBounds(int iColumn, double & lower, double & upper, int force)
{
    if ((force && 1) == 0) {
      if (lower > lower_[iColumn])
	COIN_DETAIL_PRINT(printf("%d odd lower going from %g to %g\n", iColumn, lower, lower_[iColumn]));
        lower = lower_[iColumn];
    } else {
        lower_[iColumn] = lower;
    }
    if ((force && 2) == 0) {
      if (upper < upper_[iColumn])
	COIN_DETAIL_PRINT(printf("%d odd upper going from %g to %g\n", iColumn, upper, upper_[iColumn]));
        upper = upper_[iColumn];
    } else {
        upper_[iColumn] = upper;
    }
    return (upper_[iColumn] >= lower_[iColumn]) ? 0 : 1;
}
