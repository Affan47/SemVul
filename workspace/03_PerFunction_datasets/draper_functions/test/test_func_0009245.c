parse_content_disposition(Mime *mime, Mime_part *part, char *token,
						  Mime_parameter *param_list)
{
  Mime_content_disposition *cd;
  Mime_parameter *param;

  if (part->disposition != NULL) {
	log_msg((LOG_ERROR_LEVEL, "parse_content_disposition: duplicate header"));
	return(-1);
  }

  cd = part->disposition = new_content_disposition(NULL);
  if (strcaseeq(token, "inline"))
	cd->disposition = MIME_DISPOSITION_INLINE;
  else if (strcaseeq(token, "attachment"))
	cd->disposition = MIME_DISPOSITION_ATTACHMENT;
  else if (strcaseeq(token, "form-data"))
	cd->disposition = MIME_DISPOSITION_FORMDATA;
  else {
	cd->disposition = MIME_DISPOSITION_UNKNOWN;
	log_msg((LOG_WARN_LEVEL,
			 "parse_content_disposition: unrecognized token"));
	log_msg((LOG_WARN_LEVEL,
			 "parse_content_disposition: %s (ignored)", token));
  }

  for (param = param_list; param != NULL; param = param->next) {
	if (strcaseeq(param->attrname, "name") && param->attrvalue != NULL)
	  cd->name = strdup(param->attrvalue);
	else if (strcaseeq(param->attrname, "filename")
			 && param->attrvalue != NULL)
	  cd->filename = strdup(param->attrvalue);
	else if (strcaseeq(param->attrname, "creation-date")
			 && param->attrvalue != NULL)
	  cd->creation_date = strdup(param->attrvalue);
	else if (strcaseeq(param->attrname, "modification-date")
			 && param->attrvalue != NULL)
	  cd->modification_date = strdup(param->attrvalue);
	else if (strcaseeq(param->attrname, "read-date")
			 && param->attrvalue != NULL)
	  cd->read_date = strdup(param->attrvalue);
	else if (strcaseeq(param->attrname, "size")
			 && param->attrvalue != NULL)
	  cd->size = strdup(param->attrvalue);
	else {
	  log_msg((LOG_WARN_LEVEL,
			   "parse_content_disposition: unrecognized parameter"));
	  log_msg((LOG_WARN_LEVEL, "parse_content_disposition: %s (ignored)",
			   param->attrname));
	}
  }

  return(0);
}
