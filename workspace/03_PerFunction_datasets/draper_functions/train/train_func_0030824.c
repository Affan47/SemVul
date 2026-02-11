ParseTopLevelStatement(FileDescriptorProto* file) {
  if (TryConsume(";")) {

    return true;
  } else if (LookingAt("message")) {
    return ParseMessageDefinition(file->add_message_type());
  } else if (LookingAt("enum")) {
    return ParseEnumDefinition(file->add_enum_type());
  } else if (LookingAt("service")) {
    return ParseServiceDefinition(file->add_service());
  } else if (LookingAt("extend")) {
    return ParseExtend(file->mutable_extension(),
                       file->mutable_message_type());
  } else if (LookingAt("import")) {
    return ParseImport(file->add_dependency());
  } else if (LookingAt("package")) {
    return ParsePackage(file);
  } else if (LookingAt("option")) {
    return ParseOption(file->mutable_options());
  } else {
    AddError("Expected top-level statement (e.g. \"message\").");
    return false;
  }
}
