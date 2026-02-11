ladeDatei(Str na) {


  if (ladeDateiLow(na, false)) return true;


  #if HAVE_LIBZ
  if (ladeDateiLow(na + ".gz", true)) {
    gDateiGezippt = true;
    return true;
  }
  #endif

  return false;
}
