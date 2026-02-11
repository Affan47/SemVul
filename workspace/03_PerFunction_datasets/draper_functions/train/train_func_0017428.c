printMaxSortSize(long nodata_count) {
  char buf[BUFSIZ];
  long long  fillmaxsize = (long long)nrows*ncols*sizeof(waterWindowType);
  long long  flowmaxsize = (long long)(nrows*ncols - nodata_count)*sizeof(sweepItem);
  long long maxneed = (fillmaxsize > flowmaxsize) ? fillmaxsize: flowmaxsize;
  maxneed =  2*maxneed;

  G_message( "total elements=%ld, nodata elements=%ld",
		(long)nrows*ncols, nodata_count);
  G_message( "largest temporary files: ");
  G_message( "\t\t FILL: %s [%d elements, %dB each]",
		  formatNumber(buf, fillmaxsize),
		  nrows * ncols, sizeof(waterWindowType));
  G_message( "\t\t FLOW: %s [%ld elements, %dB each]",
		  formatNumber(buf, flowmaxsize),
		  (long)(nrows * ncols - nodata_count), sizeof(sweepItem));
  G_message( "Will need at least %s space available in %s",
		  formatNumber(buf, maxneed),
		  getenv(STREAM_TMPDIR));

#ifdef HAVE_STATVFS_H
  fprintf(stderr, "Checking current space in %s: ", getenv(STREAM_TMPDIR));
  struct statvfs statbuf;
  statvfs(getenv(STREAM_TMPDIR), &statbuf);

  float avail = statbuf.f_bsize*statbuf.f_bavail;
  fprintf(stderr, "available %ld blocks x %ldB = %.0fB",
		  (long)statbuf.f_bavail, statbuf.f_bsize, avail);
  if (avail > maxneed) {
	fprintf(stderr, ". OK.\n");
  } else {
	fprintf(stderr, ". Not enough space available.\n");
	exit(EXIT_FAILURE);
  }
#endif
}
