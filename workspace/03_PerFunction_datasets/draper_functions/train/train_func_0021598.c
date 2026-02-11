onEntryValueChange(VisuUiNumericalEntry *numericalEntry, gpointer data _U_)
{
  gboolean valid;
  double valueDouble;

  valid = parsePrintedValue(numericalEntry, &valueDouble);

  if (!valid)
    printStoredValue(numericalEntry);
  else
    {
      if (valueDouble != numericalEntry->printed_value)
        visu_ui_numerical_entry_setValue(numericalEntry, valueDouble);
    }
}
