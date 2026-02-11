ask_for_card (ctrl_t ctrl, const unsigned char *shadow_info, char **r_kid)
{
  int rc, i;
  char *serialno;
  int no_card = 0;
  char *desc;
  char *want_sn, *want_kid;
  int want_sn_displen;

  *r_kid = NULL;

  rc = parse_shadow_info (shadow_info, &want_sn, &want_kid);
  if (rc)
    return rc;


  want_sn_displen = strlen (want_sn);
  if (want_sn_displen == 20 && want_sn[19] == '0')
    want_sn_displen--;

  for (;;)
    {
      rc = agent_card_serialno (ctrl, &serialno);
      if (!rc)
        {
          log_debug ("detected card with S/N %s\n", serialno);
          i = strcmp (serialno, want_sn);
          xfree (serialno);
          serialno = NULL;
          if (!i)
            {
              xfree (want_sn);
              *r_kid = want_kid;
              return 0;
            }
        }
      else if (gpg_err_code (rc) == GPG_ERR_CARD_NOT_PRESENT)
        {
          log_debug ("no card present\n");
          rc = 0;
          no_card = 1;
        }
      else
        {
          log_error ("error accessing card: %s\n", gpg_strerror (rc));
        }

      if (!rc)
        {
          if (asprintf (&desc,
                    "%s:%%0A%%0A"
                    "  \"%.*s\"",
                        no_card
                        ? _("Please insert the card with serial number")
                        : _("Please remove the current card and "
                            "insert the one with serial number"),
                    want_sn_displen, want_sn) < 0)
            {
              rc = out_of_core ();
            }
          else
            {
              rc = agent_get_confirmation (ctrl, desc, NULL, NULL, 0);
              xfree (desc);
            }
        }
      if (rc)
        {
          xfree (want_sn);
          xfree (want_kid);
          return rc;
        }
    }
}
