configureUserIdentityRequest(T_ASC_Parameters *params)
{
  OFCondition cond = EC_Normal;
  switch (opt_identMode)
  {
    case ASC_USER_IDENTITY_USER:
    {
      cond = ASC_setIdentRQUserOnly(params, opt_user, opt_identResponse);
      return cond;
    }
    case ASC_USER_IDENTITY_USER_PASSWORD:
    {
      cond = ASC_setIdentRQUserPassword(params, opt_user, opt_password, opt_identResponse);
      return cond;
    }
    case ASC_USER_IDENTITY_KERBEROS:
    case ASC_USER_IDENTITY_SAML:
    {
      OFFile identFile;
      if (!identFile.fopen(opt_identFile.c_str(), "rb"))
      {
        OFString openerror;
        identFile.getLastErrorString(openerror);
        OFLOG_ERROR(storescuLogger, "Unable to open Kerberos or SAML file: " << openerror);
        return EC_IllegalCall;
      }

      offile_off_t result = identFile.fseek(0, SEEK_END);
      if (result != 0)
        return EC_IllegalParameter;
      offile_off_t filesize = identFile.ftell();
      identFile.rewind();
      if (filesize > 65535)
      {
        OFLOG_INFO(storescuLogger, "Kerberos or SAML file is larger than 65535 bytes, bytes after that position are ignored");
        filesize = 65535;
      }

      char *buf = new char[OFstatic_cast(unsigned int, filesize)];
      size_t bytesRead = identFile.fread(buf, 1, OFstatic_cast(size_t, filesize));
      identFile.fclose();
      if (bytesRead == 0)
      {
        OFLOG_ERROR(storescuLogger, "Unable to read Kerberos or SAML info from file: File empty?");
        delete[] buf;
        return EC_IllegalCall;
      }
      if (opt_identMode == ASC_USER_IDENTITY_KERBEROS)
        cond = ASC_setIdentRQKerberos(params, buf, bytesRead, opt_identResponse);
      else
        cond = ASC_setIdentRQSaml(params, buf, bytesRead, opt_identResponse);
      delete[] buf;
      break;
    }
    default:
    {
      cond = EC_IllegalCall;
    }
  }
  if (cond.bad())
  {
    OFString temp_str;
    OFLOG_FATAL(storescuLogger, DimseCondition::dump(temp_str, cond));
  }
  return cond;
}
