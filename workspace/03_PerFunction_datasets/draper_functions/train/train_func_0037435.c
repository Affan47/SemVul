parse_old_device_line(char drive)
{
    char name[MAXPATHLEN];
    int items;
    long offset;


    finish_drive_clause();


    purge(drive, file_nr);


    append();
    items = sscanf(token,"%c %s %i %i %i %i %li",
		   &devices[cur_dev].drive,name,&devices[cur_dev].fat_bits,
		   &devices[cur_dev].tracks,&devices[cur_dev].heads,
		   &devices[cur_dev].sectors, &offset);
    devices[cur_dev].offset = (off_t) offset;
    switch(items){
	case 2:
	    devices[cur_dev].fat_bits = 0;

	case 3:
	    devices[cur_dev].sectors = 0;
	    devices[cur_dev].heads = 0;
	    devices[cur_dev].tracks = 0;

	case 6:
	    devices[cur_dev].offset = 0;

	default:
	    break;
	case 0:
	case 1:
	case 4:
	case 5:
	    syntax("bad number of parameters", 1);
	    exit(1);
    }
    if(!devices[cur_dev].tracks){
	devices[cur_dev].sectors = 0;
	devices[cur_dev].heads = 0;
    }

    devices[cur_dev].drive = toupper(devices[cur_dev].drive);
    maintain_default_drive(devices[cur_dev].drive);
    if (!(devices[cur_dev].name = strdup(name))) {
	printOom();
	exit(1);
    }
    finish_drive_clause();
    pos=0;
}
