db_match_database(const char *db_driver, const char *db_name,
                             const char *db_address, int db_port)
{
   bool match;

   if (db_driver) {
      match = strcasecmp(m_db_driver, db_driver) == 0 &&
              bstrcmp(m_db_name, db_name) &&
              bstrcmp(m_db_address, db_address) &&
              m_db_port == db_port &&
              m_dedicated == false;
   } else {
      match = bstrcmp(m_db_name, db_name) &&
              bstrcmp(m_db_address, db_address) &&
              m_db_port == db_port &&
              m_dedicated == false;
   }
   return match;
}
