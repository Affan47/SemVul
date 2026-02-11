write_image_to_file(unsigned char *filename)
{
  int 		status = 0;
  unsigned char header[20];

  printf("Saving file to disk: %s\n",filename);


  imagefile_fd = creat(filename,0644);
      if ( imagefile_fd < 0 ) {
            perror("kmc_read(open)");
            exit(1);
            }

  sprintf( header, "P5\n%d %d\n255\n", hsize, vsize);
  status = write( imagefile_fd, &header[0], strlen(header) );
  if ( status < 0 || status != strlen(header) ) {

        perror("kmc_write(image)");
        return status;
        }

  status = write( imagefile_fd, image, hsize*vsize );
  if ( status < 0 || status != hsize*vsize ) {

        perror("kmc_write(image)");
        return status;
        }

  close(imagefile_fd);
  return 0;
}
