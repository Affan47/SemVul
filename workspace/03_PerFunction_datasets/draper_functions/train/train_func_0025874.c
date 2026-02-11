password_user(G_CONST_RETURN gchar *username, G_CONST_RETURN gchar *password)
{
    FILE *fp;
    char *user_pass, *encrypted_pass;

    if( ! user_exists(username) )
    {


	return;
    }

    user_pass = allocate(8192);


    encrypted_pass = encrypt_password(password);

    if( encrypted_pass == NULL )
    {

	printf("Crypt error: using the chpass(wd) program instead\n");

#if defined USE_LINUX
	sprintf(user_pass, "echo %s:%s | chpasswd", username, password);
#endif


#if defined USE_OPENBSD || USE_NETBSD || USE_FREEBSD
	sprintf(user_pass, "echo %s:%s | chpass", username, password);
#endif


#if defined USE_DARWIN

	printf("Darwin functions are defined in osx_functions, this is a bug\n");
	sprintf(user_pass, "echo passwd/username %s:%s", username, password);
#endif

    }
    else
      {


#if defined USE_LINUX
	sprintf(user_pass, "usermod -p '%s' %s", encrypted_pass, username);
#endif

#if defined USE_OPENSBD || USE_NETBSD || USE_FREEBSD || USE_AIX || USE_HPUX
	sprintf(user_pass, "pw usermod -p '%s' %s", encrypted_pass, username);
#endif

#if defined USE_DARWIN
	sprintf(user_pass, "echo manually change the password: passwd/username '%s' %s", encrypted_pass, username);
#endif

      }


    if((fp=popen(user_pass,"w"))==NULL)
    {
        perror("popen");


    }
    else
      pclose(fp);

#if defined USE_DARWIN
    printf("Send me a mail describing your systems way of changing a users password\n");
    printf("Then i can fix it.\n");
#endif

    free(user_pass);
}
