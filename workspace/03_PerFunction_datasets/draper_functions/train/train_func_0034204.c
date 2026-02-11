read_scan_script (j_compress_ptr cinfo, char * filename)


{
  FILE * fp;
  int scanno, ncomps, termchar;
  long val;
  jpeg_scan_info * scanptr;
#define MAX_SCANS  100
  jpeg_scan_info scans[MAX_SCANS];

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Can't open scan definition file %s\n", filename);
    return FALSE;
  }
  scanptr = scans;
  scanno = 0;

  while (read_scan_integer(fp, &val, &termchar)) {
    if (scanno >= MAX_SCANS) {
      fprintf(stderr, "Too many scans defined in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    scanptr->component_index[0] = (int) val;
    ncomps = 1;
    while (termchar == ' ') {
      if (ncomps >= MAX_COMPS_IN_SCAN) {
	fprintf(stderr, "Too many components in one scan in file %s\n",
		filename);
	fclose(fp);
	return FALSE;
      }
      if (! read_scan_integer(fp, &val, &termchar))
	goto bogus;
      scanptr->component_index[ncomps] = (int) val;
      ncomps++;
    }
    scanptr->comps_in_scan = ncomps;
    if (termchar == ':') {
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Ss = (int) val;
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Se = (int) val;
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Ah = (int) val;
      if (! read_scan_integer(fp, &val, &termchar))
	goto bogus;
      scanptr->Al = (int) val;
    } else {

      scanptr->Ss = 0;
      scanptr->Se = DCTSIZE2-1;
      scanptr->Ah = 0;
      scanptr->Al = 0;
    }
    if (termchar != ';' && termchar != EOF) {
bogus:
      fprintf(stderr, "Invalid scan entry format in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    scanptr++, scanno++;
  }

  if (termchar != EOF) {
    fprintf(stderr, "Non-numeric data in file %s\n", filename);
    fclose(fp);
    return FALSE;
  }

  if (scanno > 0) {


    scanptr = (jpeg_scan_info *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  scanno * SIZEOF(jpeg_scan_info));
    MEMCOPY(scanptr, scans, scanno * SIZEOF(jpeg_scan_info));
    cinfo->scan_info = scanptr;
    cinfo->num_scans = scanno;
  }

  fclose(fp);
  return TRUE;
}
