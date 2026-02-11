cbf_tobase32k(cbf_file *infile, cbf_file *outfile, size_t size)
{
	#define maxlen 30
	unsigned char  *txt = NULL;
        char *enc = NULL;
        size_t* pencsize;
        size_t encsize = 0;
        size_t sz = 0;
	size_t  encchars = 0;
	int bigEndian = 0;
	unsigned char tmp[3];
	int count_w = 0;
	int rav = 0;
	unsigned char b;
	int count_enc=0;
	int new_l =0;
	tmp[2] = '\0';
        txt = (unsigned char *) malloc(sizeof(char) *maxlen + 1);
	txt[maxlen] = '\0';
        pencsize = &encsize;
	      sz =0;
	      while(sz<maxlen)
	      {
		      int a =0;
		      if((a = cbf_get_character(infile)) !=EOF)
		      {
			      b = a;
			      txt[sz] =b;
		      }
		      else
		      {
		                     break;
		      }
		      sz++;


              }
       bigEndian = cbf_isBigEndian();

	if(bigEndian != 0) {
		cbf_put_character(outfile, '\xFF');
		cbf_put_character(outfile, '\xFE');
	} else {
		 cbf_put_character(outfile, '\xFE');
		 cbf_put_character(outfile, '\xFF');
	}

		while(sz > 0)
        	{
			if(sz <30)
			{
				rav = 15 - ((sz*8)%15);
			}
                	enc = cbf_encode32k_bit_op(txt, sz, pencsize);
                	cbf_endianFix(enc ,*pencsize, 0, bigEndian);
            count_w = 0;
			while(count_w<*pencsize)
			{
				cbf_put_character(outfile, enc[count_w]);
				count_w++;
				count_enc++;
			}
			if(new_l == 0)
			{
				new_l++;
			}
			else if(new_l == 3)
			{
				cbf_put_character(outfile, '\x00');
				cbf_put_character(outfile, '\x0A');
				new_l =0;
			}


			encchars += *pencsize;

                	if(enc){
                        	free(enc);
                        	*pencsize = 0;
                	}


			sz =0;
	    		  while(sz<maxlen)
	      		{
		      		int a =0;
		      		if((a = cbf_get_character(infile)) !=EOF)
		      {
			      b = a;
			      txt[sz] =b;
		      }
		      else
		      {
		                     break;
		      }
		      sz++;
			}


		}
	     if(rav>=8 && rav<15)
	      {
		      if(cbf_isBigEndian() !=0)
		      {
			      cbf_put_character(outfile, '\x3D');
			      cbf_put_character(outfile, '\x00');
		      }
		      else
		      {
			      cbf_put_character(outfile, '\x00');
			      cbf_put_character(outfile, '\x3D');
		      }
		}

			      cbf_put_character(outfile, '\xEF');
			      cbf_put_character(outfile, '\xBB');
			      cbf_put_character(outfile, '\xBF');
	free(txt);
	return 0;
}
