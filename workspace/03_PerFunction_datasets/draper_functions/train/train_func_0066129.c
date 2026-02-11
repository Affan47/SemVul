DropDatabase()
{

   std::ostringstream SQLStatement;

   if (debug >0)
      cout << "Dropping a previous ht://Check database called '"
      << MySQLDB << "'" << endl;

   SQLStatement << "DROP DATABASE " << MySQLDB;


   if (Query (SQLStatement.str()) == -1)
      return 0;

   return 1;
}
