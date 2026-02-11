GetNameOfCol( int iCol ) const

{
    if( iCol < 0 || iCol >= (int) aoFields.size() )
        return "";

    else
        return aoFields[iCol].sName;
}
