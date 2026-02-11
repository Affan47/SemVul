DoOnRuleTableKeyDown (int keycode)
{
   int selrow = RuleTable->GetGridCursorRow ();
   wxString ts;
   if (keycode == WXK_UP)
   {
      if (selrow == 0)
         return;
      SwapRows (selrow - 1, selrow);
      RuleTable->MoveCursorUp (false);
      RuleTable->SelectRow (selrow - 1);
   }
   else if (keycode == WXK_DOWN)
   {
      if (selrow == RuleTable->GetNumberRows() - 1)
         return;
      SwapRows (selrow, selrow + 1);
      RuleTable->MoveCursorDown (false);
      RuleTable->SelectRow (selrow + 1);
   }
}
