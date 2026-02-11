gt_lookup_datum_index(const char* datum_str, const char* module)
{
  datum_mapping_t* d;
  int result;
  const char* name = datum_str;

  for (d = gt_mps_datum_names; (d->jeeps_name); d++) {
    if (case_ignore_strcmp(name, d->mps_name) == 0) {
      name = d->jeeps_name;
      break;
    }
  }

  result = GPS_Lookup_Datum_Index(name);

  if (result < 0) {
    char* tmp;
    xasprintf(&tmp, "%s mean", datum_str);
    result = GPS_Lookup_Datum_Index(tmp);
    xfree(tmp);
  }

  is_fatal(result < 0,
           "%s: Unsupported datum (%s)! See GPSBabel help for supported datums.",
           module, datum_str);

  return result;
}
