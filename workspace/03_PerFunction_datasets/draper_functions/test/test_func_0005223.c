list_otps (int argc, char **argv, char *inuser)
{
    void *db;
    struct passwd *pw;

    db = otp_db_open ();
    if(db == NULL)
	errx (1, "otp_db_open failed");

    if (inuser)
	print_otp_entry_for_name(db, inuser);
    else

	while ((pw = getpwent()))
	    print_otp_entry_for_name(db, pw->pw_name);

    otp_db_close (db);
    return 0;
}
