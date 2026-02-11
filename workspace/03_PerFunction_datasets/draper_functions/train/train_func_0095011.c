SetEditors()
{
   int cnt = mGrid->GetNumberRows();

   for (int i = 0; i < cnt; i++) {
      wxString label = mGrid->GetCellValue(i, 0);
      if (label.CmpNoCase(LABEL_GENRE) == 0) {
         mGrid->SetCellEditor(i, 1, mGrid->GetDefaultEditorForType(wxT("Combo")));
      }
      else {
         mGrid->SetCellEditor(i, 1, NULL);
      }
   }
}
