error(std::error_code ec) {
  if (!ec)
    return false;
  errs() << "LLVMSymbolizer: error reading file: " << ec.message() << ".\n";
  return true;
}
