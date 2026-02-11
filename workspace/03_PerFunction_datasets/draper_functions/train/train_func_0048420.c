cpl_parameter_duplicate(const cpl_parameter *self)
{

    cpl_parameter *_self = NULL;


    if (self == NULL) {
        cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    _self = cx_malloc(sizeof(cpl_parameter));

    _self->name = cx_strdup(self->name);
    _self->context = cx_strdup(self->context);
    _self->description = cx_strdup(self->description);
    _self->usertag = cx_strdup(self->usertag);

    _self->class = self->class;
    _self->data = NULL;

    switch (_self->class) {
    case CPL_PARAMETER_CLASS_VALUE:
        _self->data = _cpl_parameter_value_new(self->data->type,
                                               sizeof(cpl_parameter_value));
        break;

    case CPL_PARAMETER_CLASS_RANGE:
        _self->data = _cpl_parameter_value_new(self->data->type,
                                               sizeof(cpl_parameter_range));
        break;

    case CPL_PARAMETER_CLASS_ENUM:
        _self->data = _cpl_parameter_value_new(self->data->type,
                                               sizeof(cpl_parameter_enum));
        break;

    default:
        cpl_parameter_delete(_self);
        cpl_error_set(cpl_func, CPL_ERROR_INVALID_TYPE);
        return NULL;
        break;
    }

    cx_assert(_self->data != NULL);

    if (_cpl_parameter_copy(_self, self)) {
        cpl_parameter_delete(_self);
        return NULL;
    }

    _self->info.f_active = self->info.f_active;
    _self->info.e_active = self->info.e_active;
    _self->info.c_active = self->info.c_active;

    _self->info.f_key = cx_strdup(self->info.f_key);
    _self->info.e_key = cx_strdup(self->info.e_key);
    _self->info.c_key = cx_strdup(self->info.c_key);

    _self->info.present = self->info.present;
    _self->info.id = self->info.id;

    return _self;

}
