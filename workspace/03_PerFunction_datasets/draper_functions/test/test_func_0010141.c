AltUTMUPSRepresentation(int prec) const {
    string utm;
    UTMUPSString(_alt_zone, _alt_easting, _alt_northing, prec, utm);
    return utm;
  }
