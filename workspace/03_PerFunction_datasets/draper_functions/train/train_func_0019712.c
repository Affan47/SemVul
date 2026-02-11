_db_unlock(const char *file, int line)
{
   int errstat;

   if ((errstat = rwl_writeunlock(&m_lock)) != 0) {
      berrno be;
      e_msg(file, line, M_FATAL, 0, "rwl_writeunlock failure. stat=%d: ERR=%s\n",
            errstat, be.bstrerror(errstat));
   }
}
