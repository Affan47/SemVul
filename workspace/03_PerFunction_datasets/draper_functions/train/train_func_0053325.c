tftpd_clientlist_remove(struct thread_data *thread,
                             struct client_info *client)
{
     struct client_info *tmp = thread->client_info;

     pthread_mutex_lock(&thread->client_mutex);
     while ((tmp->next != client) && (tmp->next != NULL))
          tmp = tmp->next;
     if (tmp->next == NULL)
          return;
     tmp->next = tmp->next->next;
     pthread_mutex_unlock(&thread->client_mutex);
}
