ps_io_fgetchars(FileData fd, int num)
{
   char *eol=NULL,*tmp;
   size_t size_of_char = sizeof(char);

   BEGINMESSAGE(ps_io_fgetchars)

   if (FD_STATUS != FD_STATUS_OKAY) {
      INFMESSAGE(aborting since status not okay)
      ENDMESSAGE(ps_io_fgetchars)
      return(NULL);
   }

   FD_BUF[FD_LINE_END] = FD_LINE_TERMCHAR;
   FD_LINE_BEGIN       = FD_LINE_END;

   do {
      if (num<0) {
         if (FD_BUF_END-FD_LINE_END) {


	    tmp = FD_BUF + FD_BUF_END;
	    eol = FD_BUF + FD_LINE_END;
	    while (eol < tmp && *eol != '\n' && *eol != '\r') eol++;
	    if (eol >= tmp) eol = NULL;
            if (eol) {
               if (*eol=='\r' && *(eol+1)=='\n') eol += 2;
               else eol++;
               break;
            }
         }
      } else {
	 if (FD_BUF_END >= FD_LINE_BEGIN+num) {
            eol = FD_BUF+FD_LINE_BEGIN+num;
            break;
         }
      }

      INFMESSAGE(no end of line yet)

      if (FD_BUF_END - FD_LINE_BEGIN > BREAK_PS_IO_FGETCHARS_BUF_SIZE) {
	INFMESSAGE(breaking line artificially)
	eol = FD_BUF + FD_BUF_END - 1;
	break;
      }

      while (FD_BUF_SIZE < FD_BUF_END+LINE_CHUNK_SIZE+1) {
         if (FD_BUF_SIZE > MAX_PS_IO_FGETCHARS_BUF_SIZE) {


            INFMESSAGE(buffer became to large)
            ENDMESSAGE(ps_io_fgetchars)
	    fprintf(stderr, "gv: ps_io_fgetchars: Fatal Error: buffer became too large.\n");
	    clean_safe_tempdir();
	    exit(-1);
         }
         if (FD_LINE_BEGIN) {
            INFMESSAGE(moving line to begin of buffer)
            ps_memmove((void*)FD_BUF,(void*)(FD_BUF+FD_LINE_BEGIN),
                    ((size_t)(FD_BUF_END-FD_LINE_BEGIN+1))*size_of_char);
            FD_BUF_END    -= FD_LINE_BEGIN;
            FD_LINE_BEGIN  = 0;
         } else {
            INFMESSAGE(enlarging buffer)


            FD_BUF_SIZE    = FD_BUF_SIZE+LINE_CHUNK_SIZE+1;
            IMESSAGE(FD_BUF_SIZE)
            FD_BUF         = XtRealloc(FD_BUF,FD_BUF_SIZE);
         }
      }

      FD_LINE_END = FD_BUF_END;

      FD_BUF_END += fread(FD_BUF+FD_BUF_END,size_of_char,LINE_CHUNK_SIZE,FD_FILE);

      FD_BUF[FD_BUF_END] = '\0';
      if (FD_BUF_END-FD_LINE_END == 0) {
         INFMESSAGE(failed to read more chars)
         ENDMESSAGE(ps_io_fgetchars)
         FD_STATUS = FD_STATUS_NOMORECHARS;
         return(NULL);
      }
   }
   while (1);

   FD_LINE_END          = eol - FD_BUF;
   FD_LINE_LEN          = FD_LINE_END - FD_LINE_BEGIN;
   FD_LINE_TERMCHAR     = FD_BUF[FD_LINE_END];
   FD_BUF[FD_LINE_END]  = '\0';
#ifdef USE_FTELL_FOR_FILEPOS
   if (FD_LINE_END==FD_BUF_END) {
      INFMESSAGE(### using ftell to get FD_FILEPOS)


      FD_FILEPOS         = GV_FTELL(FD_FILE);
   } else
#endif
      FD_FILEPOS        += FD_LINE_LEN;

   ENDMESSAGE(ps_io_fgetchars)
   return(FD_BUF+FD_LINE_BEGIN);
}
