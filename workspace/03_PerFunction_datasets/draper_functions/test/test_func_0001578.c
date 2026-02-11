usage (char *msg)
{
  fprintf (stderr, "Usage: %s [-hvqf] [devname ...]\n", prog_name);
  fprintf (stderr, "\t-h: print this help message\n");
  fprintf (stderr, "\t-v: be more verbose (can be used multiple times)\n");
  fprintf (stderr, "\t-q: be quiet (print only devices, no comments)\n");
  fprintf (stderr, "\t-f: force opening devname as SCSI even if it looks "
	   "like USB\n");
  fprintf (stderr, "\t-p: enable scanning for parallel port devices\n");
#ifdef HAVE_LIBUSB
  fprintf (stderr, "\t-F file: try to detect chipset from given "
	   "/proc/bus/usb/devices file\n");
#endif
  if (msg)
    fprintf (stderr, "\t%s\n", msg);
}
