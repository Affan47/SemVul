BlockSemanticTableToString(BlockSemanticTable uiTable) {
  string charString = BlockSemanticTableToCharString(uiTable);
  wstring result(charString.begin(), charString.end());
  return result;
}
