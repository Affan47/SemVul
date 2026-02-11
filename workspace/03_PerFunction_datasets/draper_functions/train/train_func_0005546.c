auth_token_import(FILE *fp, Auth_token_mode mode, int replace,
				  char *pin_constraints)
{
  int linenum, saw_root;
  char *errmsg, *line, *startp;
  Auth_token *token;
  Ds *ds;
  Kwv *kwv;
  Kwv_xml *xml;

  ds = ds_init(NULL);
  dsio_set(ds, fp, NULL, 0, 0);
  ds->delnl_flag = 1;
  ds->crnl_flag = 1;

  linenum = 1;
  errmsg = NULL;
  saw_root = 0;

  while ((line = dsio_gets(ds)) != NULL) {
	startp = line;
	while (*startp == ' ' || *startp == '\t')
	  startp++;
	if (*startp == '\0' || *startp == '#') {
	  linenum++;
	  continue;
	}

	if ((xml = kwv_xml_parse(NULL, startp, &errmsg)) == NULL)
	  goto fail;
	if (xml->type == KWV_XML_COMMENT) {
	  linenum++;
	  continue;
	}

	if (!saw_root) {
	  if (!streq(xml->el_name, "otp_tokens")) {
		errmsg = "Invalid root element";
		goto fail;
	  }
	  if (xml->type == KWV_XML_EMPTY_TAG) {
		saw_root = 2;
		break;
	  }
	  if (xml->type != KWV_XML_START_TAG) {
		errmsg = "Invalid root tag";
		goto fail;
	  }
	  saw_root = 1;
	  linenum++;
	  continue;
	}

	if (xml->type == KWV_XML_END_TAG && streq(xml->el_name, "otp_tokens")) {
	  saw_root = 2;
	  break;
	}

	if (!streq(xml->el_name, "otp_token")) {
	  errmsg = "Invalid element";
	  goto fail;
	}

	kwv = xml->kwv_attrs;
	if ((token = import_token(kwv, mode, replace, pin_constraints,
							  &errmsg)) != NULL) {
	  if (auth_token_set(token) == -1) {
		errmsg = "Could not write account record";
		goto fail;
	  }
	}
	else if (errmsg != NULL)
	  goto fail;

	linenum++;
  }

  if (saw_root == 2)
	return(0);

  if (ferror(fp) || !feof(fp)) {
	errmsg = "Input error";
	goto fail;
  }

  errmsg = "XML parse error";

 fail:
  if (errmsg == NULL)
	fprintf(stderr, "Error at line %d: syntax error", linenum);
  else
	fprintf(stderr, "Line %d: %s", linenum, errmsg);
  if (line != NULL)
	fprintf(stderr, ": %s", line);
  fprintf(stderr, "\n");

  return(-1);
}
