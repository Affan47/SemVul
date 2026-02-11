process_message_list (const char *domain, message_list_ty *mlp)
{
  if (string_list_member (domain_names, domain))

    ;
  else

    message_list_remove_if_not (mlp, is_message_selected);
}
