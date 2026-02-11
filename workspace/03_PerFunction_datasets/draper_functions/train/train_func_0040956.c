mailimap_namespace_data_parse(mailstream * fd,
                                         MMAPString * buffer, size_t * indx,
                                         struct mailimap_namespace_data ** result,
                                         size_t progr_rate, progress_function * progr_fun)
{
  size_t cur_token;
  int r;
  int res;
  struct mailimap_namespace_item * personal_namespace;
  struct mailimap_namespace_item * other_namespace;
  struct mailimap_namespace_item * shared_namespace;
  struct mailimap_namespace_data * ns;

  cur_token = * indx;

  r = mailimap_token_case_insensitive_parse(fd, buffer,
                                            &cur_token, "NAMESPACE");
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  r = mailimap_space_parse(fd, buffer, &cur_token);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  r = mailimap_namespace_item_parse(fd, buffer, &cur_token, &personal_namespace, progr_rate, progr_fun);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  r = mailimap_namespace_item_parse(fd, buffer, &cur_token, &other_namespace, progr_rate, progr_fun);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto free_personal;
  }

  r = mailimap_namespace_item_parse(fd, buffer, &cur_token, &shared_namespace, progr_rate, progr_fun);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto free_other;
  }

  ns = mailimap_namespace_data_new(personal_namespace, other_namespace, shared_namespace);
  if (ns == NULL) {
    res = MAILIMAP_ERROR_MEMORY;
    goto free_shared;
  }

  * result = ns;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;

free_shared:
  if (shared_namespace != NULL) {
    mailimap_namespace_item_free(shared_namespace);
  }
free_other:
  if (other_namespace != NULL) {
    mailimap_namespace_item_free(other_namespace);
  }
free_personal:
  if (personal_namespace != NULL) {
    mailimap_namespace_item_free(personal_namespace);
  }
err:
  return res;
}
