afp_server_login(struct afp_server *server,
	char * mesg, unsigned int *l, unsigned int max)
{
	int rc;

	rc=afp_dologin(server,server->using_uam,
		server->username,server->password);

	switch(rc) {
	case -1:
		*l+=snprintf(mesg,max-*l,
			"Could not find a valid UAM\n");
		goto error;
	case kFPAuthContinue:
		*l+=snprintf(mesg,max-*l,
			"Authentication method unsupported by AFPFS\n");
		goto error;
	case kFPBadUAM:
		*l+=snprintf(mesg,max-*l,
			"Specified UAM is unknown\n");
		goto error;
	case kFPBadVersNum:
		*l+=snprintf(mesg,max-*l,
			"Server does not support this AFP version\n");
	case kFPCallNotSupported:
	case kFPMiscErr:
		*l+=snprintf(mesg,max-*l,
			"Already logged in\n");
		break;
	case kFPNoServer:
		*l+=snprintf(mesg,max-*l,
			"Authentication server not responding\n");
		goto error;
	case kFPPwdExpiredErr:
	case kFPPwdNeedsChangeErr:
		*l+=snprintf(mesg,max-*l,
			"Warning: password needs changing\n");
		goto error;
	case kFPServerGoingDown:
		*l+=snprintf(mesg,max-*l,
			"Server going down, so I can't log you in.\n");
		goto error;
	case kFPUserNotAuth:
		*l+=snprintf(mesg,max-*l,
			"Authentication failed\n");
		goto error;
	case 0: break;
	default:
		*l+=snprintf(mesg,max-*l,
			"Unknown error, maybe username/passwd needed?\n");
		goto error;
	}

	if (server->flags & kSupportsReconnect) {


		if (server->need_resume) {
			resume_token(server);
			server->need_resume=0;
		} else {
			setup_token(server);
		}
	}

	return 0;
error:
	return 1;
}
