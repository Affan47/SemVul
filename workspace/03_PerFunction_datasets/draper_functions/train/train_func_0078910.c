write(dimeOutput * const file)
{
  if (file->writeGroupCode(0) && file->writeString(this->objectName))
    return dimeObject::write(file);
  return false;
}
