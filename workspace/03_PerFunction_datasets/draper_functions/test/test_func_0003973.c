externalId(const ExternalId &id, Boolean outputFile)
{
  const StringC *str = id.publicIdString();
  if (str) {
    os() << pubidCode;
    outputString(*str);
    os() << nl;
  }
  str = id.systemIdString();
  if (str) {
    os() << sysidCode;
    outputString(*str);
    os() << nl;
  }
  if (outputFile && id.effectiveSystemId().size()) {
    os() << fileCode;
    outputString(id.effectiveSystemId());
    os() << nl;
  }
}
