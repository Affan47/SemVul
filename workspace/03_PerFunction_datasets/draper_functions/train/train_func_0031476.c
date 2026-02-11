convertToSignExtendedInteger(integerPart *parts, unsigned int width,
                                      bool isSigned,
                                      roundingMode rounding_mode,
                                      bool *isExact) const
{
  lostFraction lost_fraction;
  const integerPart *src;
  unsigned int dstPartsCount, truncatedBits;

  *isExact = false;


  if (category == fcInfinity || category == fcNaN)
    return opInvalidOp;

  dstPartsCount = partCountForBits(width);

  if (category == fcZero) {
    APInt::tcSet(parts, 0, dstPartsCount);

    *isExact = !sign;
    return opOK;
  }

  src = significandParts();


  if (exponent < 0) {

    APInt::tcSet(parts, 0, dstPartsCount);


    truncatedBits = semantics->precision -1U - exponent;
  } else {


    unsigned int bits = exponent + 1U;


    if (bits > width)
      return opInvalidOp;

    if (bits < semantics->precision) {

      truncatedBits = semantics->precision - bits;
      APInt::tcExtract(parts, dstPartsCount, src, bits, truncatedBits);
    } else {

      APInt::tcExtract(parts, dstPartsCount, src, semantics->precision, 0);
      APInt::tcShiftLeft(parts, dstPartsCount, bits - semantics->precision);
      truncatedBits = 0;
    }
  }


  if (truncatedBits) {
    lost_fraction = lostFractionThroughTruncation(src, partCount(),
                                                  truncatedBits);
    if (lost_fraction != lfExactlyZero &&
        roundAwayFromZero(rounding_mode, lost_fraction, truncatedBits)) {
      if (APInt::tcIncrement(parts, dstPartsCount))
        return opInvalidOp;
    }
  } else {
    lost_fraction = lfExactlyZero;
  }


  unsigned int omsb = APInt::tcMSB(parts, dstPartsCount) + 1;

  if (sign) {
    if (!isSigned) {

      if (omsb != 0)
        return opInvalidOp;
    } else {


      if (omsb == width && APInt::tcLSB(parts, dstPartsCount) + 1 != omsb)
        return opInvalidOp;


      if (omsb > width)
        return opInvalidOp;
    }

    APInt::tcNegate (parts, dstPartsCount);
  } else {
    if (omsb >= width + !isSigned)
      return opInvalidOp;
  }

  if (lost_fraction == lfExactlyZero) {
    *isExact = true;
    return opOK;
  } else
    return opInexact;
}
