inColRange(int c_)
{ return((c_>=firstColumn()&&c_<=lastColumn())||(c_>=0&&c_<=fixedColumns()-1))?MSTrue:MSFalse; }
