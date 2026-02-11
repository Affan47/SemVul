parsePublic()
{
  if (parseParam(minimumLiteral) != literalParam) {
    message(CatalogMessages::literalExpected);
    return;
  }
  StringC publicId;
  param_.swap(publicId);
  if (!parseArg())
    return;
  catalog_->addPublicId(publicId, param_, paramLoc_, override_);
}
