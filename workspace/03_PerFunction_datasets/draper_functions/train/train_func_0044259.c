SwapRows (int row1, int row2)
{
   int t;
   ExtImportItem *t1, *t2;
   wxString ts;
   if (row1 == row2)
      return;
   if (row1 > row2)
   {
      t = row1;
      row1 = row2;
      row2 = t;
   }
   ExtImportItems *items = wxGetApp().mImporter->GetImportItems();
   t1 = items->Detach(row1);
   t2 = items->Detach(row1);
   items->Insert (t1, row1);
   items->Insert (t2, row1);
   for (int i = 0; i < RuleTable->GetNumberCols(); i++)
   {
      ts = RuleTable->GetCellValue (row2, i);
      RuleTable->SetCellValue (row2, i, RuleTable->GetCellValue (row1, i));
      RuleTable->SetCellValue (row1, i, ts);
   }
}
