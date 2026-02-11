_giraffe_psfexp_ctor(GiModel *self, const GiModelData *model)
{

    cx_assert(self != NULL);
    cx_assert(model != NULL);

    self->name = cx_strdup(model->name);
    self->type = model->type;

    self->model = model->eval;


    self->arguments.names = cpl_propertylist_new();

    cpl_propertylist_append_int(self->arguments.names, "x", 0);

    self->arguments.count = cpl_propertylist_get_size(self->arguments.names);
    self->arguments.values = cpl_matrix_new(self->arguments.count, 1);


    self->parameters.names = cpl_propertylist_new();

    cpl_propertylist_append_int(self->parameters.names, "Amplitude",
                                LMP_AMPL);
    cpl_propertylist_append_int(self->parameters.names, "Center",
                                LMP_CENT);
    cpl_propertylist_append_int(self->parameters.names, "Background",
                                LMP_BACK);
    cpl_propertylist_append_int(self->parameters.names, "Width1",
                                LMP_WID1);
    cpl_propertylist_append_int(self->parameters.names, "Width2",
                                LMP_WID2);

    self->parameters.count =
        cpl_propertylist_get_size(self->parameters.names);
    self->parameters.values = cpl_matrix_new(self->parameters.count, 1);

    return;

}
