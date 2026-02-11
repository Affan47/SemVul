drawHeadings(Window window_)
{
  if (mapped()==MSTrue&&frozen()==MSFalse)
   {
     drawFixedColumnHeadings(window_);
     drawHeadings(window_,firstColumn(),lastColumn());
   }
}
