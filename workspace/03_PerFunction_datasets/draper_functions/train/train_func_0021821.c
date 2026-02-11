setuser() {


	if (pw) {
		setgroups(0, NULL);
		setregid(pw->pw_gid, pw->pw_gid);
		setreuid(pw->pw_uid, pw->pw_uid);
	}
}
