displaymessage( const ASCString& text, int num  )
{
   const char* a = text.c_str();

   tstringa stringtooutput;
   memset (stringtooutput, 0, sizeof ( stringtooutput ));
   stringtooutput[0] =  new char[200];
   stringtooutput[0][0] = 0;
   char* b = stringtooutput[0];

   int linenum = 0;

   while ( *a ) {
      if (*a == '\n') {
         *b = 0;
         linenum++;
         stringtooutput[linenum] = new char[200];
         b = stringtooutput[linenum];
         *b = 0;
      } else {
        *b = *a;
        b++;
      }
      a++;
   }

   *b = 0;


   bool displayInternally = true;


   #ifndef NoStdio
   if ( num == 2 )
      displayInternally = false;
   #endif


   if ( num == 2 )
      displayLogMessage(1, text );


   if ( !displayInternally ) {
      for ( int i=0; i<= linenum ;i++ )
          fprintf(stderr,"%s\n",stringtooutput[i]);
      fflush( stderr );
   } else {
      #ifdef _WIN322_
        if ( !gameStartupComplete && num==2 ) {
           MessageBox(NULL, text.c_str(), "Fatal Error", MB_ICONERROR | MB_OK | MB_TASKMODAL );
           exit(1);
        }
      #endif

      if ( legacyEventSystemActive() ) {
         static int messageboxopen = 0;
         if ( messageboxopen )
            return;

         messageboxopen++;
         if ( messagebox ) {
            if ( messagebox->boxstatus )
               messagebox->done();
            delete messagebox;
            messagebox = NULL;
         }

         messagebox = new tdisplaymessage;

         if ( num== 2 )
            messagebox->init( stringtooutput, num, linenum, "~q~uit program");
         else
            messagebox->init( stringtooutput, num, linenum);

         if (num != 0 ) {
            messagebox->run();
            messagebox->done();
            delete messagebox;
            messagebox = NULL;
         }

         messageboxopen--;
      } else {
         MessagingHub::Instance().warning( text );
      }
   }

   if ( num == 2 ) {
      #ifdef _WIN32_

           MessageBox(NULL, text.c_str(), "Fatal Error", MB_ICONERROR | MB_OK | MB_TASKMODAL );
           exit(1);

      #endif
      exit ( 1 );
   }

   for ( int i=linenum; i>=0 ;i-- )
      delete[]  stringtooutput[i];
}
