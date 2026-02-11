IsRcn( R )
rdsrec_list	*R;
{

  if(    GetRdsLayer(R)==RDS_ALU1
      || GetRdsLayer(R)==RDS_ALU2
      || GetRdsLayer(R)==RDS_ALU3
      || GetRdsLayer(R)==RDS_ALU4
      || GetRdsLayer(R)==RDS_ALU5
      || GetRdsLayer(R)==RDS_ALU6
      || GetRdsLayer(R)==RDS_POLY )
    return( 1 );
  return(0);
}
