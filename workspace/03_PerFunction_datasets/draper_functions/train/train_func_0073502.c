unmap(void)
{
  if (mapped()==MSTrue)
   {
     pulldownMenus();
     MSWidgetCommon::unmap();
     reset();
   }
}
