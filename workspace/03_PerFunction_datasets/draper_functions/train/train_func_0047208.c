Register() {
  static ExternalizeStringExtension* externalize_extension = NULL;
  if (externalize_extension == NULL)
    externalize_extension = new ExternalizeStringExtension;
  static v8::DeclareExtension externalize_extension_declaration(
      externalize_extension);
}
