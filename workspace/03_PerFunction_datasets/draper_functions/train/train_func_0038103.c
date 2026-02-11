chkClose(Agraph_t * g)
{
    gdata *data;

    data = gData(g);
    if (data->lock & 1)
	data->lock |= 2;
    else
	agclose(g);
}
