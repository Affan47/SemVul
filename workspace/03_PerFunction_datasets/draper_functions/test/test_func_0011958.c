Delete(int index, int count)
{
   if (!modified_)
      modified_ = true;
   return TextBuffer::Delete(index, count);
}
