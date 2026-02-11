sasl_errstring(int saslerr,
			   const char *langlist __attribute__((unused)),
			   const char **outlang)
{
  if (outlang) *outlang="en-us";

  switch(saslerr)
    {
    case SASL_CONTINUE: return "another step is needed in authentication";
    case SASL_OK:       return "successful result";
    case SASL_FAIL:     return "generic failure";
    case SASL_NOMEM:    return "no memory available";
    case SASL_BUFOVER:  return "overflowed buffer";
    case SASL_NOMECH:   return "no mechanism available";
    case SASL_BADPROT:  return "bad protocol / cancel";
    case SASL_NOTDONE:  return "can't request information until later in exchange";
    case SASL_BADPARAM: return "invalid parameter supplied";
    case SASL_TRYAGAIN: return "transient failure (e.g., weak key)";
    case SASL_BADMAC:   return "integrity check failed";
    case SASL_NOTINIT:  return "SASL library is not initialized";

    case SASL_INTERACT:   return "needs user interaction";
    case SASL_BADSERV:    return "server failed mutual authentication step";
    case SASL_WRONGMECH:  return "mechanism doesn't support requested feature";

    case SASL_BADAUTH:    return "authentication failure";
    case SASL_NOAUTHZ:    return "authorization failure";
    case SASL_TOOWEAK:    return "mechanism too weak for this user";
    case SASL_ENCRYPT:    return "encryption needed to use mechanism";
    case SASL_TRANS:      return "One time use of a plaintext password will enable requested mechanism for user";
    case SASL_EXPIRED:    return "passphrase expired, has to be reset";
    case SASL_DISABLED:   return "account disabled";
    case SASL_NOUSER:     return "user not found";
    case SASL_BADVERS:    return "version mismatch with plug-in";
    case SASL_UNAVAIL:    return "remote authentication server unavailable";
    case SASL_NOVERIFY:   return "user exists, but no verifier for user";
    case SASL_PWLOCK:     return "passphrase locked";
    case SASL_NOCHANGE:   return "requested change was not needed";
    case SASL_WEAKPASS:   return "passphrase is too weak for security policy";
    case SASL_NOUSERPASS: return "user supplied passwords are not permitted";
    case SASL_NEED_OLD_PASSWD: return "sasl_setpass needs old password in order "
				"to perform password change";
    case SASL_CONSTRAINT_VIOLAT: return "sasl_setpass can't store a property because "
			        "of a constraint violation";
    case SASL_BADBINDING: return "channel binding failure";

    default:   return "undefined error!";
    }

}
