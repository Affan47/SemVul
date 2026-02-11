rcoxml_parse_ref (char *val, rRCORef * out)
{

  out->type = RCO_REF_NONE;
  out->rawPtr = RCO_NULL_PTR;
  out->ptr = NULL;

  if (!strcasecmp (val, "nothing")) {
    return TRUE;
  }

  char *colon = strchr (val, ':');

  if (!colon)
    return FALSE;
  colon[0] = '\0';

  if (!strcasecmp (val, "event"))
    out->type = RCO_REF_EVENT;
  else if (!strcasecmp (val, "text"))
    out->type = RCO_REF_TEXT;
  else if (!strcasecmp (val, "image"))
    out->type = RCO_REF_IMG;
  else if (!strcasecmp (val, "model"))
    out->type = RCO_REF_MODEL;
  else if (!strcasecmp (val, "font"))
    out->type = RCO_REF_FONT;
  else if (!strcasecmp (val, "object2"))
    out->type = RCO_REF_OBJ2;
  else if (!strcasecmp (val, "anim"))
    out->type = RCO_REF_ANIM;
  else if (!strcasecmp (val, "object"))
    out->type = RCO_REF_OBJ;

  colon[0] = ':';
  colon++;

  if (out->type == RCO_REF_NONE) {
    if (sscanf (val, "unknown%i", (int *) &(out->type))) {


      out->rawPtr = strtol (colon, NULL, 10);
      return TRUE;
    } else {
      return FALSE;
    }
  }

  out->ptr = malloc (strlen (colon) + 1);
  strcpy ((char *) out->ptr, colon);

  return TRUE;
}
