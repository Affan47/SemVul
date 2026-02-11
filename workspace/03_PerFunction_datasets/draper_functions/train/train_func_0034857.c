nopassword_warning_msg(int gotloc) {

	char str1[] =
"###############################################################\n"
"#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\n"
"#@                                                           @#\n"
"#@  **  WARNING  **  WARNING  **  WARNING  **  WARNING  **   @#\n"
"#@                                                           @#\n"
"#@        YOU ARE RUNNING X11VNC WITHOUT A PASSWORD!!        @#\n"
"#@                                                           @#\n"
"#@  This means anyone with network access to this computer   @#\n"
"#@  may be able to view and control your desktop.            @#\n"
"#@                                                           @#\n"
"#@ >>> If you did not mean to do this Press CTRL-C now!! <<< @#\n"
"#@                                                           @#\n"
"#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\n"
;
	char str2[] =
"#@                                                           @#\n"
"#@  You can create an x11vnc password file by running:       @#\n"
"#@                                                           @#\n"
"#@       x11vnc -storepasswd password /path/to/passfile      @#\n"
"#@  or   x11vnc -storepasswd /path/to/passfile               @#\n"
"#@  or   x11vnc -storepasswd                                 @#\n"
"#@                                                           @#\n"
"#@  (the last one will use ~/.vnc/passwd)                    @#\n"
"#@                                                           @#\n"
"#@  and then starting x11vnc via:                            @#\n"
"#@                                                           @#\n"
"#@      x11vnc -rfbauth /path/to/passfile                    @#\n"
"#@                                                           @#\n"
"#@  an existing ~/.vnc/passwd file from another VNC          @#\n"
"#@  application will work fine too.                          @#\n"
"#@                                                           @#\n"
"#@  You can also use the -passwdfile or -passwd options.     @#\n"
"#@  (note -passwd is unsafe if local users are not trusted)  @#\n"
"#@                                                           @#\n"
"#@  Make sure any -rfbauth and -passwdfile password files    @#\n"
"#@  cannot be read by untrusted users.                       @#\n"
"#@                                                           @#\n"
"#@  Use x11vnc -usepw to automatically use your              @#\n"
"#@  ~/.vnc/passwd or ~/.vnc/passwdfile password files.       @#\n"
"#@  (and prompt you to create ~/.vnc/passwd if neither       @#\n"
"#@  file exists.)  Under -usepw, x11vnc will exit if it      @#\n"
"#@  cannot find a password to use.                           @#\n"
"#@                                                           @#\n"
"#@                                                           @#\n"
"#@  Even with a password, the subsequent VNC traffic is      @#\n"
"#@  sent in the clear.  Consider tunnelling via ssh(1):      @#\n"
"#@                                                           @#\n"
"#@    http://www.karlrunge.com/x11vnc/#tunnelling            @#\n"
"#@                                                           @#\n"
"#@  Or using the x11vnc SSL options: -ssl and -stunnel       @#\n"
"#@                                                           @#\n"
"#@  Please Read the documention for more info about          @#\n"
"#@  passwords, security, and encryption.                     @#\n"
"#@                                                           @#\n"
"#@    http://www.karlrunge.com/x11vnc/faq.html#faq-passwd    @#\n"
;
	char str3[] =
"#@                                                           @#\n"
"#@  You are using the -localhost option and that is a good   @#\n"
"#@  thing!! Especially if you ssh(1) into this machine and   @#\n"
"#@  use port redirection.  Nevertheless, without a password  @#\n"
"#@  other users could possibly do redirection as well to     @#\n"
"#@  gain access to your desktop.                             @#\n"
;
	char str4[] =
"#@                                                           @#\n"
"#@  To disable this warning use the -nopw option, or put     @#\n"
"#@  'nopw' on a line in your ~/.x11vncrc file.               @#\n"
"#@                                                           @#\n"
"#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\n"
"###############################################################\n"
;
	char str5[] =
"###############################################################\n\n"
;
	if (inetd) {
		return;
	}

	fprintf(stderr, "%s", str1);
	fflush(stderr);
#if !PASSWD_REQUIRED
	usleep(750 * 1000);
#endif
	if (!quiet) {
		fprintf(stderr, "%s", str2);
		if (gotloc) {
			fprintf(stderr, "%s", str3);
		}
		fprintf(stderr, "%s", str4);
	} else {
		fprintf(stderr, "%s", str5);
	}
	fflush(stderr);
#if !PASSWD_REQUIRED
	usleep(250 * 1000);
#endif
}
