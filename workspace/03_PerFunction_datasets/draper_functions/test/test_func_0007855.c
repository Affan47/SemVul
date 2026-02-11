exists(file_status status) {
  return status_known(status) && status.type() != file_type::file_not_found;
}
