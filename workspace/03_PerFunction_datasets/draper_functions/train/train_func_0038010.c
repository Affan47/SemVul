set ( int num, dReal value )
{
    switch ( num )
    {
    case dParamCFM:
        cfm = value;
        break;
    case dParamERP:
        erp = value;
        break;
    }
}
