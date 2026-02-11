inpowerz_changed(NeuralTrainControls *controls, GtkAdjustment *adj)
{
    NeuralNetworkData *nndata = &controls->args->nn->data;
    if (controls->in_update)
        return;
    nndata->inpowerz = gwy_adjustment_get_int(adj);
    GWY_RESOURCE(controls->args->nn)->is_modified = TRUE;
}
