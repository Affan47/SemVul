vsbValueUpdate(void)
{
  if (vsb()->value()<firstLine()) scrollDown(firstLine()-vsb()->value());
  else if (vsb()->value()>firstLine()) scrollUp(vsb()->value()-firstLine());
}
