PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(2);

   S.StartStatic(_("Mouse Bindings (default values, not configurable)"), 1);
   {
      mList = S.AddListControlReportMode();
   }
   S.EndStatic();
}
