IsDatabaseValid(std::string path)
{
  if(!kwsys::SystemTools::FileExists(path.c_str(), true))
    {
    return false;
    }

  mds::SQLiteDatabase db;
  bool result = db.Open(path.c_str());
  result &= db.ExecuteQuery("SELECT * FROM dirty_resource");
  while(db.GetNextRow());
  result &= db.Close();
  return result;
}
