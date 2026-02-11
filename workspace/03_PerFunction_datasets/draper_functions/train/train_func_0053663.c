loadrdsfig( Figure, Name, Mode )

  rdsfig_list *Figure;
  char        *Name;
  char         Mode;
{
  if ( RDS_IN == RDS_GDS_FORMAT )
  {
    gdsloadrdsfig( Figure, Name, Mode );
  }
  else
  if ( RDS_IN == RDS_CIF_FORMAT )
  {
    cifloadrdsfig( Figure, Name, Mode );
  }
  else
  {
    rtlerror( RTL_UNKNOWN_RDS_IN, RDS_IN );
  }
}
