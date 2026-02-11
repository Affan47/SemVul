gearman_client_run_block_tasks(gearman_client_st *client, gearman_task_st* exit_task)
{
  if (client == NULL)
  {
    return GEARMAN_INVALID_ARGUMENT;
  }

  if (client->task_list == NULL)
  {
    return GEARMAN_SUCCESS;
  }


  gearman_return_t rc;
  {
    PUSH_BLOCKING(client->universal);

    rc= _client_run_tasks(client, exit_task);
  }

  if (gearman_failed(rc))
  {
    if (rc == GEARMAN_COULD_NOT_CONNECT)
    {
      gearman_reset(client->universal);
    }

    if (gearman_universal_error_code(client->universal) != rc and rc != GEARMAN_COULD_NOT_CONNECT)
    {
      assert(gearman_universal_error_code(client->universal) == rc);
    }
  }

  return rc;
}
