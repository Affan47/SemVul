ppp_available(void)
{
    int s, ok, fd, err;
    struct ifreq ifr;
    int    size;
    int    my_version, my_modification, my_patch;
    int osmaj, osmin, ospatch;


    uname(&utsname);
    osmaj = osmin = ospatch = 0;
    sscanf(utsname.release, "%d.%d.%d", &osmaj, &osmin, &ospatch);
    kernel_version = KVERSION(osmaj, osmin, ospatch);

    fd = open("/dev/ppp", O_RDWR);
    if (fd >= 0) {
	new_style_driver = 1;


	driver_version = 2;
	driver_modification = 4;
	driver_patch = 0;
	close(fd);
	return 1;
    }
    err = errno;

    if (kernel_version >= KVERSION(2,3,13)) {
	error("Couldn't open the /dev/ppp device: %m");
	if (errno == ENOENT)
	    no_ppp_msg =
		"You need to create the /dev/ppp device node by\n"
		"executing the following command as root:\n"
		"	mknod /dev/ppp c 108 0\n";
	else if (errno == ENODEV || errno == ENXIO)
	    no_ppp_msg =
		"Please load the ppp_generic kernel module.\n";
	return 0;
    }


    no_ppp_msg =
	"This system lacks kernel support for PPP.  This could be because\n"
	"the PPP kernel module could not be loaded, or because PPP was not\n"
	"included in the kernel configuration.  If PPP was included as a\n"
	"module, try `/sbin/modprobe -v ppp'.  If that fails, check that\n"
	"ppp.o exists in /lib/modules/`uname -r`/net.\n"
	"See README.linux file in the ppp distribution for more details.\n";


    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0)
	return 0;

    strlcpy (ifr.ifr_name, "ppp0", sizeof (ifr.ifr_name));
    ok = ioctl(s, SIOCGIFFLAGS, (caddr_t) &ifr) >= 0;


    if (!ok) {
	if (ppp_registered()) {
	    strlcpy (ifr.ifr_name, "ppp0", sizeof (ifr.ifr_name));
	    ok = ioctl(s, SIOCGIFFLAGS, (caddr_t) &ifr) >= 0;
	}
    }


    if (ok)
	ok = ioctl (s, SIOCGIFHWADDR, (caddr_t) &ifr) >= 0;

    if (ok && ((ifr.ifr_hwaddr.sa_family & ~0xFF) != ARPHRD_PPP))
	ok = 0;


    if (ok) {
	char   abBuffer [1024];

	ifr.ifr_data = abBuffer;
	size = ioctl (s, SIOCGPPPVER, (caddr_t) &ifr);
	if (size < 0) {
	    error("Couldn't read driver version: %m");
	    ok = 0;
	    no_ppp_msg = "Sorry, couldn't verify kernel driver version\n";

	} else {
	    decode_version(abBuffer,
			   &driver_version,
			   &driver_modification,
			   &driver_patch);


	    decode_version(VERSION,
			   &my_version,
			   &my_modification,
			   &my_patch);


	    if (driver_version != my_version)
		ok = 0;


	    if (driver_modification < 3) {
		if (driver_modification >= 2) {

		    driver_is_old = 1;
		} else {
		    ok = 0;
		}
	    }

	    close (s);
	    if (!ok) {
		slprintf(route_buffer, sizeof(route_buffer),
			 "Sorry - PPP driver version %d.%d.%d is out of date\n",
			 driver_version, driver_modification, driver_patch);

		no_ppp_msg = route_buffer;
	    }
	}
    }
    return ok;
}
