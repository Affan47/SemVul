WriteDescriptorSet(
    const vector<const FileDescriptor*> parsed_files) {
  FileDescriptorSet file_set;

  if (imports_in_descriptor_set_) {
    set<const FileDescriptor*> already_seen;
    for (int i = 0; i < parsed_files.size(); i++) {
      GetTransitiveDependencies(
          parsed_files[i], &already_seen, file_set.mutable_file());
    }
  } else {
    for (int i = 0; i < parsed_files.size(); i++) {
      parsed_files[i]->CopyTo(file_set.add_file());
    }
  }

  int fd;
  do {
    fd = open(descriptor_set_name_.c_str(),
              O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);
  } while (fd < 0 && errno == EINTR);

  if (fd < 0) {
    perror(descriptor_set_name_.c_str());
    return false;
  }

  io::FileOutputStream out(fd);
  if (!file_set.SerializeToZeroCopyStream(&out)) {
    cerr << descriptor_set_name_ << ": " << strerror(out.GetErrno()) << endl;
    out.Close();
    return false;
  }
  if (!out.Close()) {
    cerr << descriptor_set_name_ << ": " << strerror(out.GetErrno()) << endl;
    return false;
  }

  return true;
}
