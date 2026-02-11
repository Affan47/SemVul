BuildFileFromDatabase(
    const FileDescriptorProto& proto) const {
  mutex_->AssertHeld();
  return DescriptorBuilder(this, tables_.get(),
                           default_error_collector_).BuildFile(proto);
}
