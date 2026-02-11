txt_header(xformat,ntrks,ldivision)
int xformat, ntrks, ldivision;
{
    division = ldivision;
    format = xformat;
    if (format != 0) {

      if(summary>0) printf("This midi file has %d tracks\n\n",ntrks);
    }
    else {

     if(summary>0) {
	     printf("This is a type 0 midi file.\n");
             printf("All the channels are in one track.\n");
             printf("You may need to process the channels separately\n\n");
            }
     }

}
