unsigned_divide(verinum num, verinum den, bool signed_result)
{
      unsigned nwid = num.len();
      while (nwid > 0 && (num.get(nwid-1) == verinum::V0))
	    nwid -= 1;

      unsigned dwid = den.len();
      while (dwid > 0 && (den.get(dwid-1) == verinum::V0))
	    dwid -= 1;

      if (dwid > nwid)
	    return verinum(verinum::V0, 1);

      den = den << (nwid-dwid);

      unsigned idx = nwid - dwid + 1;
      verinum result (verinum::V0, signed_result ? idx + 1 : idx);
      if (signed_result) {
	    result.set(idx, verinum::V0);
	    result.has_sign(true);
      }
      while (idx > 0) {
	    if (den <= num) {
		  verinum dif = num - den;
		  num = dif;
		  result.set(idx-1, verinum::V1);
	    }
	    den = den >> 1;
	    idx -= 1;
      }

      return result;
}
