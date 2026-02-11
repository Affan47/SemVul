parse_xml_auth_prompt(const char **attr)
{
  char *errmsg, *type;
  Auth_prompt *prompt;

  prompt = ALLOC(Auth_prompt);
  prompt->type = NULL;
  prompt->label = NULL;
  prompt->varname = NULL;
  prompt->next = NULL;

  auth_reply_prompt_attr_tab[0].value = &type;
  auth_reply_prompt_attr_tab[1].value = &prompt->label;
  auth_reply_prompt_attr_tab[2].value = &prompt->varname;
  if (parse_xml_attr(auth_reply_prompt_attr_tab, attr, &errmsg) == -1) {
	parse_xml_set_error(errmsg);
	free(prompt);
	return(NULL);
  }

  if (!streq(type, "password") && !streq(type, "text")
	  && !streq(type, "error") && !streq(type, "label")) {
	parse_xml_set_error("Invalid \"prompt\" attribute");
	free(prompt);
	return(NULL);
  }
  prompt->type = type;

  if ((streq(prompt->type, "password") || streq(prompt->type, "text"))
	  && prompt->varname == NULL) {
	parse_xml_set_error("Missing \"varname\" attribute");
	free(prompt);
	return(NULL);
  }

  if ((streq(prompt->type, "error") || streq(prompt->type, "label"))
	  && prompt->label == NULL) {
	parse_xml_set_error("Missing \"label\" attribute");
	free(prompt);
	return(NULL);
  }

  return(prompt);
}
