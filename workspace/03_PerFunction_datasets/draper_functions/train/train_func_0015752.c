updateSensitivity(void)
{
  _fieldValue->sensitive(sensitive());
  _fieldLabel->sensitive(sensitive());
   if (sensitive()==MSTrue) XSetFillStyle(display(),drawGC(),FillSolid);
   else XSetFillStyle(display(),drawGC(),FillStippled);
  redraw();
}
