startTableRow(StyleObj *style)
{
  Table *table = tableStack_.head();
  if (table) {
    table->rowStyle = style;
    table->currentColumn = 0;
    table->inTableRow = 1;
    table->rowConnectableLevel = connectionStack_.head()->connectableLevel;
  }
  currentFOTBuilder().startTableRow();
}
