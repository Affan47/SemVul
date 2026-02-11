print_gnu_note (Elf_Internal_Note *pnote)
{
  switch (pnote->type)
    {
    case NT_GNU_BUILD_ID:
      {
	unsigned long i;

	printf (_("    Build ID: "));
	for (i = 0; i < pnote->descsz; ++i)
	  printf ("%02x", pnote->descdata[i] & 0xff);
	printf ("\n");
      }
      break;

    case NT_GNU_ABI_TAG:
      {
	unsigned long os, major, minor, subminor;
	const char *osname;

	os = byte_get ((unsigned char *) pnote->descdata, 4);
	major = byte_get ((unsigned char *) pnote->descdata + 4, 4);
	minor = byte_get ((unsigned char *) pnote->descdata + 8, 4);
	subminor = byte_get ((unsigned char *) pnote->descdata + 12, 4);

	switch (os)
	  {
	  case GNU_ABI_TAG_LINUX:
	    osname = "Linux";
	    break;
	  case GNU_ABI_TAG_HURD:
	    osname = "Hurd";
	    break;
	  case GNU_ABI_TAG_SOLARIS:
	    osname = "Solaris";
	    break;
	  case GNU_ABI_TAG_FREEBSD:
	    osname = "FreeBSD";
	    break;
	  case GNU_ABI_TAG_NETBSD:
	    osname = "NetBSD";
	    break;
	  default:
	    osname = "Unknown";
	    break;
	  }

	printf (_("    OS: %s, ABI: %ld.%ld.%ld\n"), osname,
		major, minor, subminor);
      }
      break;
    }

  return 1;
}
