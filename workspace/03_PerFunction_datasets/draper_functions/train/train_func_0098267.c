__getItemType()
{
  if (__itemName == "elements") {
    return FunctionExpressionMeshReferences::element;
  }
  if (__itemName == "vertices") {
    return FunctionExpressionMeshReferences::vertex;
  }
  return FunctionExpressionMeshReferences::undefined;
}
