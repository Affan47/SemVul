write_gray_image(char *filename, char *format)
{
  int           status = 0;
  unsigned char header[20];
  int 		filenamelength, i, j;
  int 		fd;


  filenamelength = strlen(filename);


  if (filenamelength != 0) {
	fd = creat(filename,0644);
	if ( fd < 0 ) {
            perror("kmc:write_gray_image(creat)");
            exit(1);
            }
	}


  if (strncmp(format,"pgm",3) == 0) sprintf(header, "P5\n%d %d\n255\n", hsize, vsize);
  if (strncmp(format,"ppm",3) == 0) sprintf(header, "P6\n%d %d\n255\n", hsize, vsize);


  if ((filenamelength == 0)&(filename!="\0")) printf("%s",header);
  if (filenamelength != 0) {
	status = write( fd, &header[0], strlen(header) );
	if ( status < 0 || status != strlen(header) ) {

            perror("kmc:write_gray_image(write)");
            return status;
            }
	}


  if (strncmp(format,"pgm",3) == 0) {

	if (filenamelength != 0){
	    status = write( fd, image, hsize*vsize );
   	    if ( status != hsize*vsize ) {

        	perror("write_gray_image(write)");
        	return status;
        	}
	    }


    if ((filenamelength == 0)&(filename!="\0")){
            for (i=0; i<hsize*vsize; i++){
                printf("%c",image[i]);
                }
	    }
	}


  if (strncmp(format,"ppm",3) == 0) {

	if (filenamelength != 0){
            for (i=0; i<hsize*vsize; i++){
            	for (j=0; j<3; j++){

		  status = write(fd, image+i, 1);
   	    	    if ( status != 1 ) {

			printf("i: %d  j: %d\n",i,j);
			printf("status: %d\n",status);
        		perror("write_gray_image(write)");
        		return status;
        	    	}
		    }
                }
	    }


    if ((filenamelength == 0)&(filename!="\0")){
            for (i=0; i<hsize*vsize; i++){
                printf("%c%c%c\n",image[i],image[i],image[i]);
                }
	    }
	}


  if (filenamelength != 0) {
	status = close(fd);
	if ( status < 0 ) {
            perror("kmc:write_gray_image(close)");
            exit(1);
            }
	}

  return 0;
}
