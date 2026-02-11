obj(int index, const PdfFile *file) const
{
  const PdfObj *obj = iObjects[index];
  if (file && obj->ref()) {
    int n = obj->ref()->value();
    return file->object(n);
  }
  return obj;
}
