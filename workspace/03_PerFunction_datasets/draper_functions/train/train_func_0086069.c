atmsw_recv_cell(netio_desc_t *nio,u_char *atm_cell,ssize_t cell_len,
                           atmsw_table_t *t)
{
   int res;

   if (cell_len != ATM_CELL_SIZE)
      return(-1);

   ATMSW_LOCK(t);
   res = atmsw_handle_cell(t,nio,atm_cell);
   ATMSW_UNLOCK(t);
   return(res);
}
