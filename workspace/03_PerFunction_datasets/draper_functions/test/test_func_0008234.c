acl_strcpy_special (char *d, char *s)
{
    for (; *s; LDAP_UTF8INC(s)) {
	switch (*s) {
	  case '.':
	  case '\\':
	  case '[':
	  case ']':
	  case '*':
	  case '+':
	  case '^':
	  case '$':
	    *d = '\\';
	    LDAP_UTF8INC(d);

	  default:
	    d += LDAP_UTF8COPY(d, s);
	}
    }
    *d = '\0';
}
