BlobModeToString(BlobMode blob_mode)
{
  const char
    *mode_string="?";

  switch (blob_mode)
  {
  case UndefinedBlobMode:
    mode_string="Undefined";
    break;
  case ReadBlobMode:
    mode_string="Read";
    break;
  case ReadBinaryBlobMode:
    mode_string="ReadBinary";
    break;
  case WriteBlobMode:
    mode_string="Write";
    break;
  case WriteBinaryBlobMode:
    mode_string="WriteBinary";
    break;
  }
  return mode_string;
}
