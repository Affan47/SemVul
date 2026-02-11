auth_check_options()
{
    lcp_options *wo = &lcp_wantoptions[0];
    int can_auth;
    int lacks_ip;


    if (our_name[0] == 0 || usehostname)
	strlcpy(our_name, hostname, sizeof(our_name));


    if (user[0] == 0 && !explicit_user)
	strlcpy(user, our_name, sizeof(user));


    if (!auth_required && !allow_any_ip && have_route_to(0) && !privileged) {
	auth_required = 1;
	default_auth = 1;
    }


    if (wo->chap_mdtype)
	wo->neg_chap = 1;


    if (auth_required) {
	allow_any_ip = 0;
	if (!wo->neg_chap && !wo->neg_upap && !wo->neg_eap) {
	    wo->neg_chap = chap_mdtype_all != MDTYPE_NONE;
	    wo->chap_mdtype = chap_mdtype_all;
	    wo->neg_upap = 1;
	    wo->neg_eap = 1;
	}
    } else {
	wo->neg_chap = 0;
	wo->chap_mdtype = MDTYPE_NONE;
	wo->neg_upap = 0;
	wo->neg_eap = 0;
    }


    lacks_ip = 0;
    can_auth = wo->neg_upap && (uselogin || have_pap_secret(&lacks_ip));
    if (!can_auth && (wo->neg_chap || wo->neg_eap)) {
	can_auth = have_chap_secret((explicit_remote? remote_name: NULL),
				    our_name, 1, &lacks_ip);
    }
    if (!can_auth && wo->neg_eap) {
	can_auth = have_srp_secret((explicit_remote? remote_name: NULL),
				    our_name, 1, &lacks_ip);
    }

    if (auth_required && !can_auth && noauth_addrs == NULL) {
	if (default_auth) {
	    option_error(
"By default the remote system is required to authenticate itself");
	    option_error(
"(because this system has a default route to the internet)");
	} else if (explicit_remote)
	    option_error(
"The remote system (%s) is required to authenticate itself",
			 remote_name);
	else
	    option_error(
"The remote system is required to authenticate itself");
	option_error(
"but I couldn't find any suitable secret (password) for it to use to do so.");
	if (lacks_ip)
	    option_error(
"(None of the available passwords would let it use an IP address.)");

	exit(1);
    }


    if (!auth_number()) {
	warn("calling number %q is not authorized", remote_number);
	exit(EXIT_CNID_AUTH_FAILED);
    }
}
