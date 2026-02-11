job_output_status_add_file(const GMJob &job,const GMConfig &config,const FileData& file) {

  std::string fname = config.ControlDir() + "/job." + job.get_id() + sfx_outputstatus;
  std::string data;
  if (!Arc::FileRead(fname, data) && errno != ENOENT) return false;
  std::ostringstream line;
  line<<file<<"\n";
  data += line.str();
  return Arc::FileCreate(fname, data) & fix_file_owner(fname,job) & fix_file_permissions(fname);
}
