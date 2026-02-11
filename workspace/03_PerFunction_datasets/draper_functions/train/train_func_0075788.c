ValidateFileOptions(FileDescriptor* file,
                                            const FileDescriptorProto& proto) {
  VALIDATE_OPTIONS_FROM_ARRAY(file, message_type, Message);
  VALIDATE_OPTIONS_FROM_ARRAY(file, enum_type, Enum);
  VALIDATE_OPTIONS_FROM_ARRAY(file, service, Service);
  VALIDATE_OPTIONS_FROM_ARRAY(file, extension, Field);


  if (!IsLite(file)) {
    for (int i = 0; i < file->dependency_count(); i++) {
      if (IsLite(file->dependency(i))) {
        AddError(
          file->name(), proto,
          DescriptorPool::ErrorCollector::OTHER,
          "Files that do not use optimize_for = LITE_RUNTIME cannot import "
          "files which do use this option.  This file is not lite, but it "
          "imports \"" + file->dependency(i)->name() + "\" which is.");
        break;
      }
    }
  }
}
