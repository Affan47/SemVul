setComment(const String &s)
{
  addField(d->commentField.isEmpty() ? "DESCRIPTION" : d->commentField, s);
}
