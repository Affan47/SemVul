validate_saml11_conditions(Icx_ctx *ctx, xmlDocPtr token_doc)
{
  xmlNodePtr conditions, root;

  if (!ctx->validate_message_conditions) {
	log_msg((LOG_INFO_LEVEL, "Not checking SAML message conditions"));
	return(1);
  }

  root = xmlDocGetRootElement(token_doc);
  for (conditions = root->children; conditions != NULL;
	   conditions = conditions->next) {
	if (conditions->type == XML_ELEMENT_NODE
		&& xmlStreq(conditions->name, CONDITIONS)
		&& xmlStreq(conditions->ns->href, NS_SAML_11))
	  break;
  }
  if (conditions == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Conditions element missing"));
	return(-1);
  }

  if (evaluate_saml11_time_conditions(ctx, conditions) == -1) {

	return(-1);
  }
  log_msg((LOG_TRACE_LEVEL, "Time conditions ok"));

  if (evaluate_saml11_child_conditions(ctx, conditions) == -1) {

	return(-1);
  }
  log_msg((LOG_TRACE_LEVEL, "Child conditions ok"));

  return(1);
}
