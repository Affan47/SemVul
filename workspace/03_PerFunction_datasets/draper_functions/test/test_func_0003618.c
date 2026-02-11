cleanup24DiskList( void ) {
	DiskIOInfo* ptr = DiskIO;
	DiskIOInfo* last = 0;

	while ( ptr ) {
		if ( ptr->alive == 0 ) {
			DiskIOInfo* newPtr;
			char sensorName[ 128 ];


			sprintf( sensorName, "disk/%s_(%d:%d)24/total", ptr->devname, ptr->major, ptr->minor );
			removeMonitor( sensorName );
			sprintf( sensorName, "disk/%s_(%d:%d)24/rio", ptr->devname, ptr->major, ptr->minor );
			removeMonitor( sensorName );
			sprintf( sensorName, "disk/%s_(%d:%d)24/wio", ptr->devname, ptr->major, ptr->minor );
			removeMonitor( sensorName );
			sprintf( sensorName, "disk/%s_(%d:%d)24/rblk", ptr->devname, ptr->major, ptr->minor );
			removeMonitor( sensorName );
			sprintf( sensorName, "disk/%s_(%d:%d)24/wblk", ptr->devname, ptr->major, ptr->minor );
			removeMonitor( sensorName );
			if ( last ) {
				last->next = ptr->next;
				newPtr = ptr->next;
			}
			else {
				DiskIO = ptr->next;
				newPtr = DiskIO;
				last = 0;
			}

			free ( ptr );
			ptr = newPtr;
		}
		else {
			ptr->alive = 0;
			last = ptr;
			ptr = ptr->next;
		}
	}
}
