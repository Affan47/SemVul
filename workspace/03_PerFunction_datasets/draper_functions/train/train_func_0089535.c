db_close_database(JCR *jcr, B_DB *mdb)
{
   if (mdb) {
      mdb->db_close_database(jcr);
   }
}
