GetValueAsDouble( const wxSheetCoords& coords )
{
    const wxString val(GetValue(coords));
    double dval = 0.0;
    val.ToDouble(&dval);

    return dval;
}
