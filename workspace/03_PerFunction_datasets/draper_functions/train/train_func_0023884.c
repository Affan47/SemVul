Insert(int index, const char* string, int count)
{
   if (!modified_)
      modified_ = true;
   if (length + count >= size)
      expand_buffer(count);
   return TextBuffer::Insert(index, string, count);
}
