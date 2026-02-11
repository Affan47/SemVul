OnRuleTableEdit (wxGridEvent& event)
{
   int row = event.GetRow();
   int col = event.GetCol();
   ExtImportItems *items = wxGetApp().mImporter->GetImportItems();
   ExtImportItem *item = &(*items)[row];
   RuleTable->SaveEditControlValue();

   wxString val = RuleTable->GetCellValue (row, col);
   int fixSpaces = wxNO;
   bool askedAboutSpaces = false;
   wxArrayString vals;
   wxString delims(wxT(":"));
   wxGetApp().mImporter->StringToList (val, delims, vals);
   switch (col)
   {
   case 0:
      item->extensions.Clear();
      break;
   case 1:
      item->mime_types.Clear();
      break;
   }

   for (size_t i = 0; i < vals.Count(); i++)
   {

      wxString trimmed = vals[i];
      trimmed.Trim().Trim(false);
      if (trimmed.Cmp(vals[i]) != 0)
      {
         if (!askedAboutSpaces)
         {
            fixSpaces = wxMessageBox(_(
"There are space characters (spaces, newlines, tabs or linefeeds) in one of \
the items. They are likely to break the pattern matching. Unless you know \
what you are doing, it is recommended to trim spaces. Do you want \
Audacity to trim spaces for you?"
            ),_("Spaces detected"), wxYES_NO);
            askedAboutSpaces = true;
         }
         if (fixSpaces != wxYES)
         {
            trimmed = vals[i];
         }
         else
         {
            vals[i] = trimmed;
         }
      }
      switch (col)
      {
      case 0:
         item->extensions.Add (trimmed);
         break;
      case 1:
         item->mime_types.Add (trimmed);
         break;
      }
   }
   if (fixSpaces == wxYES)
   {
      wxString vals_as_string;
      for (size_t i = 0; i < vals.Count(); i++)
      {
         if (i > 0)
            vals_as_string.Append (wxT(":"));
         vals_as_string.Append (vals[i]);
      }
      RuleTable->SetCellValue (row, col, vals_as_string);
   }

   RuleTable->AutoSizeColumns ();
}
