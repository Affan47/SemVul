programmer_echo(int port, char ch) {
	unsigned char command;

   command = 2;
   write(port,&command,1);
   write(port,&ch,1);
   read(port,&command,1);
   if( command != ch ) {
      printf("DEBUG: Bad echo: %c != %c\n", command, ch);
      return -1;
   }

   return 0;
}
