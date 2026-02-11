dumpInput(StringRef File) {
  ErrorOr<OwningBinary<Binary>> BinaryOrErr = createBinary(File);
  if (std::error_code EC = BinaryOrErr.getError())
    return EC;

  Binary &Binary = *BinaryOrErr.get().getBinary();

  if (ObjectFile *Obj = dyn_cast<ObjectFile>(&Binary))
    return dumpObject(*Obj);

  return obj2yaml_error::unrecognized_file_format;
}
