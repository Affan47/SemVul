job_input_write_file(const GMJob &job,const GMConfig &config,std::list<FileData> &files) {
  std::string fname = config.ControlDir() + "/job." + job.get_id() + sfx_input;
  return job_Xput_write_file(fname,files) & fix_file_owner(fname,job) & fix_file_permissions(fname);
}
