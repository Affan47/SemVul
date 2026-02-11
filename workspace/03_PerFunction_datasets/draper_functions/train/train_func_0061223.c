swapcd(int newslot)
{
        int fd;
        int status=0;


	if(newslot == slot)
		return;
	slot=newslot;


        fd = open (device, 0);

        if(mounton) umount(device);

        if (fd < 0) {
                fprintf (stderr, "ascdc: open failed for `%s': %s\n",
                         device, strerror (errno));
        }


	if (ioctl (fd, CDROM_CHANGER_NSLOTS) < 0)
	  status += ioctl (fd, CDROM_SELECT_DISC, slot);
	else
	  status += ioctl (fd, CDROM_SELECT_DISC, slot) < 0;

        if (status != 0) {
                fprintf (stderr,
                         "%s: CDROM_SELECT_DISC ioctl failed for ascdc: %s\n",
                         device, strerror (errno));
        }


        status += close (fd);
        if (status != 0) {
                fprintf (stderr, "ascdc: close failed for `%s': %s\n",
                         device, strerror (errno));
			 }

	if(status==0)
	{
		if(slot==0) CurrentXPM=cd0XPM;
        	if(slot==1) CurrentXPM=cd1XPM;
        	if(slot==2) CurrentXPM=cd2XPM;
		if(slot==3) CurrentXPM=cd3XPM;
                RedrawWindow(&CurrentXPM);

		if(mounton)
                  {  status=mount(device,mountdir,"iso9660", 0xC0ED0001,0);
                     fprintf(stderr, "errno %i Mounter %s\n",errno, mountdir);
		     if(status!=0)
			{
 			   if(autoplay)
			   system(cdplayer);
			}
		      else fprintf(stderr, "errno %i Mounter %s\n",errno, mountdir);
		  }

	}


}
