getJulianCentury() {
    if (isINVALID(julianCentury)) {
        julianCentury = (getJulianDay() - 2415020.0) / 36525.0;
    }
    return julianCentury;
}
