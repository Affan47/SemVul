eet_connection_new(Eet_Read_Cb  *eet_read_cb,
                   Eet_Write_Cb *eet_write_cb,
                   const void   *user_data)
{
   Eet_Connection *conn;

   if ((!eet_read_cb) || (!eet_write_cb)) return NULL;

   conn = calloc(1, sizeof (Eet_Connection));
   if (!conn) return NULL;
   conn->eet_read_cb = eet_read_cb;
   conn->eet_write_cb = eet_write_cb;
   conn->user_data = (void *)user_data;
   return conn;
}
