SharedDtor() {
  if (name_part_ != &_default_name_part_) {
    delete name_part_;
  }
  if (this != default_instance_) {
  }
}
