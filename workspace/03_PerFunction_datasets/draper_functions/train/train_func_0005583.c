data_write(void)
{
  if (dbname) {
    strncpy(file_out->name, dbname, PDB_DBNAMELEN);
  } else {
    strncpy(file_out->name, out_fname, PDB_DBNAMELEN);
  }


  file_out->name[PDB_DBNAMELEN-1] = 0;
  file_out->attr = PDB_FLAG_BACKUP;
  file_out->ctime = file_out->mtime = current_time() + 2082844800U;

  file_out->type = MYWPT;
  file_out->creator = MYCREATOR;
  file_out->version = 1;

  waypt_disp_all(my_write_wpt);
}
