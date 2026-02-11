init(void)
{
  _title=label()->label();
  _highlightThickness=0;
  _shadowThickness=2;
  _titleAlignment=MSLeft|MSCenter;
  shadowStyle(MSEtchedIn);
  int offset=shadowThickness()+highlightThickness()+margin();
  label()->highlightThickness(0);
  label()->shadowThickness(0);
  label()->margin(4);
  label()->dynamic(MSTrue);
  label()->moveTo(offset,offset);
  if (label()->columns()>0) label()->map();
}
