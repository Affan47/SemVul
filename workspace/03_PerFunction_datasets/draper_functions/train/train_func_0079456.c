file_isCommentEnd ()
{
  int i, i2;
  i = file_currentcomment;
  for (i2 = 0; i2 < (int) strlen (file_commentend [i]); i2 ++)
    if (file_buffer [file_ptr + i2] != file_commentend [i] [i2])
      break;
  if (i2 == (int) strlen (file_commentend [i]))
  {
    for (i = 0; i < i2; i ++)
      (void) file_nextChar ();
    return 1;
  }
  return 0;
}
