showUnitCargoSummary( ContainerBase* cb )
{
    UnitSummaryWindow isw( NULL, PG_Rect( -1, -1, 500, 700 ),  "cargo summary", new VehicleCounterFactory( cb ), NULL );
    isw.Show();
    isw.RunModal();
}
