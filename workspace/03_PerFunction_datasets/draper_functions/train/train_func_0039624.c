mhdriver_initialize(mailsession * session)
{
  struct mh_session_state_data * data;

  data = malloc(sizeof(* data));
  if (data == NULL)
    goto err;

  data->mh_session = NULL;
  data->mh_cur_folder = NULL;

  data->mh_subscribed_list = clist_new();
  if (data->mh_subscribed_list == NULL)
    goto free;

  session->sess_data = data;

  return MAIL_NO_ERROR;

 free:
  free(data);
 err:
  return MAIL_ERROR_MEMORY;
}
