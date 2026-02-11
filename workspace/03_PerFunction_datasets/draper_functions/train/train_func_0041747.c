formatOutput(MSString &buffer_,unsigned row_)
{
  if (MSView::model()!=0&&row_<list().length()) buffer_=list()(row_);
  return buffer_.string();
}
