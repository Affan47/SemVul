stan_map(p_name,pp_mem,p_length)

char   *p_name;
char  **pp_mem;
ulong  *p_length;
{
 ulong  file_length;
 char  *p_err;
 FILE  *infile;
 ulong  num_bytes;
 char  *p_bytes;
 char  *p_curr;
 long  bytes_left;


 p_err=file_len(p_name,&file_length);
 if (p_err != NULL)
    return p_err;


 p_bytes=(char *) mm_temp((size_t) file_length+BLK_FUDGE);


 if (file_length==0)
   {
    *pp_mem   = p_bytes;
    *p_length = 0;
    return NULL;
   }


 infile=fopen(p_name,"r");
 if (infile==FOPEN_F)
    return "Error fopen()ing input file (for reading).";


 p_curr     = p_bytes;
 bytes_left = file_length+1;

 while (!feof(infile))
   {
    int bytes_try;
    int bytes_read;


    bytes_try = bytes_left >= ((ulong) (INT_MAX-LIM_FUDGE)) ?
                  (int) INT_MAX-LIM_FUDGE : (int) bytes_left;


    *p_curr=EOS;


    fgets(p_curr,bytes_try+1,infile);
    if (ferror(infile))
      {
       fclose(infile);
       return "Error fgets()ing the input file.";
      }


    bytes_read  = strlen(p_curr);
    p_curr     += bytes_read;
    bytes_left -= bytes_read;


    as_cold(bytes_left >=0,
            "stan_map: Text representation was longer than binary rep.");
   }

 num_bytes=(file_length+1)-bytes_left;


 if (fclose(infile) == FCLOSE_F)
    return "Error fclose()ing input file.";


 *pp_mem   = p_bytes;
 *p_length = num_bytes;
 return NULL;
}
