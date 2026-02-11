Broadcast(unsigned long event_type, unsigned long num_datum,
	       unsigned long data1, unsigned long data2, unsigned long data3,
	       unsigned long data4, unsigned long data5, unsigned long data6,
	       unsigned long data7)
{
  int i;
  unsigned long body[10];

  body[0] = START_FLAG;
  body[1] = event_type;
  body[2] = num_datum+3;

  if(num_datum>0)
    body[3] = data1;
  if(num_datum>1)
    body[4] = data2;
  if(num_datum>2)
    body[5] = data3;
  if(num_datum>3)
    body[6] = data4;
  if(num_datum>4)
    body[7] = data5;
  if(num_datum>5)
    body[8] = data6;
  if(num_datum>6)
    body[9] = data7;

  for(i=0;i<npipes;i++)
    PositiveWrite(i,body, (num_datum+3)*sizeof(unsigned long));
}
