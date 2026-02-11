mailimap_msg_att_item_parse(mailstream * fd, MMAPString * buffer,
			    size_t * indx,
			    struct mailimap_msg_att_item ** result,
			    size_t progr_rate,
			    progress_function * progr_fun)
{
  int type;
  struct mailimap_msg_att_dynamic * msg_att_dynamic;
  struct mailimap_msg_att_static * msg_att_static;
  size_t cur_token;
  struct mailimap_msg_att_item * item;
  int r;
  int res;

  cur_token = * indx;

  msg_att_dynamic = NULL;
  msg_att_static = NULL;

  type = MAILIMAP_MSG_ATT_ITEM_ERROR;

  r = mailimap_msg_att_dynamic_parse(fd, buffer, &cur_token,
				     &msg_att_dynamic,
				     progr_rate, progr_fun);
  if (r == MAILIMAP_NO_ERROR)
    type = MAILIMAP_MSG_ATT_ITEM_DYNAMIC;

  if (r == MAILIMAP_ERROR_PARSE) {
    r = mailimap_msg_att_static_parse(fd, buffer, &cur_token,
				      &msg_att_static,
				      progr_rate, progr_fun);
    if (r == MAILIMAP_NO_ERROR)
      type = MAILIMAP_MSG_ATT_ITEM_STATIC;
  }

  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  item = mailimap_msg_att_item_new(type, msg_att_dynamic, msg_att_static);
  if (item == NULL) {
    res = MAILIMAP_ERROR_MEMORY;
    goto free;
  }

  * result = item;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;

 free:
  if (msg_att_dynamic != NULL)
    mailimap_msg_att_dynamic_free(msg_att_dynamic);
  if (msg_att_static != NULL)
    mailimap_msg_att_static_free(msg_att_static);
 err:
  return res;
}
