hypervisor_close_conn(hypervisor_conn_t *conn)
{
   if (conn != NULL) {
      conn->active = FALSE;
      shutdown(conn->client_fd,2);
      pthread_join(conn->tid,NULL);

      fclose(conn->in);
      fclose(conn->out);

      shutdown(conn->client_fd,2);
      close(conn->client_fd);

      hypervisor_remove_conn(conn);
      free(conn);
   }
}
