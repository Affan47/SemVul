emit_roles_reply_failed(FILE *fp, char *reason)
{
  Roles_reply rr;
  Roles_reply_failed failed;

  rr.ok = NULL;
  rr.failed = &failed;
  rr.status = NULL;
  if (reason == NULL)
	failed.reason = "unknown";
  else
	failed.reason = escape_xml_attribute(reason, '\"');

  emit_xml_header(fp, "roles_reply");
  fprintf(fp, "%s", make_xml_roles_reply(&rr));
  emit_xml_trailer(fp);
}
