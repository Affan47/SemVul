MakeLayerInvisible(Layer)

int Layer;
{
    int Row,Column,Lmin;

    if (Layer <= NumLayerTable) {
        Lmin = Parameters.kpVisibleLayerMenuRow *
            Parameters.kpLayersPerMenuRow + 1;

        LayerTable[Layer].klAttributes &= ~VISIBLE;
        if (Layer >= Lmin &&  Layer < Lmin + Parameters.kpLayersPerMenuRow) {

            Row = FB.fNumRows;
            Column = (Layer - 1 - (((Layer-1)/Parameters.kpLayersPerMenuRow) *
                Parameters.kpLayersPerMenuRow)) * 6 + 1;
            LtBox(Column,Row,ERASE,Layer);
        }
    }
}
