pine_header_forbidden(char *name)
{
    char **p;
    static char *forbidden_headers[] = {
	"sender",
	"x-sender",
	"x-x-sender",
	"date",
	"received",
	"message-id",
	"in-reply-to",
	"path",
	"resent-message-id",
	"resent-date",
	"resent-from",
	"resent-sender",
	"resent-to",
	"resent-cc",
	"resent-reply-to",
	"mime-version",
	"content-type",
	"x-priority",
	"user-agent",
	NULL
    };

    for(p = forbidden_headers; *p; p++)
      if(!strucmp(name, *p))
	break;

    return((*p) ? 1 : 0);
}
