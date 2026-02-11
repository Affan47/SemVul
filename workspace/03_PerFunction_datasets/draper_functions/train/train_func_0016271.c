giraffe_psf_config_create(cpl_parameterlist* list)
{

    cpl_parameter *p;

    GiPsfConfig *self = NULL;


    if (list == NULL) {
        return NULL;
    }

    self = cx_calloc(1, sizeof *self);

    p = cpl_parameterlist_find(list, "giraffe.psf.model");
    self->profile = cx_strdup(cpl_parameter_get_string(p));

    if (cx_strncasecmp(self->profile, "psfexp", 6) == 0) {
        self->width = 16.;
    }
    else {
        self->width = 4.;
    }

    p = cpl_parameterlist_find(list, "giraffe.psf.binsize");
    self->binsize = cpl_parameter_get_int(p);

    if (self->binsize < 1) {
        self->binsize = 1;
    }

    p = cpl_parameterlist_find(list, "giraffe.psf.maxwidth");
    self->maxwidth = cpl_parameter_get_double(p);

    if (self->width > 0.) {
        p = cpl_parameterlist_find(list, "giraffe.psf.width");
        self->width = cpl_parameter_get_double(p);
    }

    if (self->width > self->maxwidth) {
        self->width = self->maxwidth;
    }

    p = cpl_parameterlist_find(list, "giraffe.psf.exponent");
    self->exponent = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.normalize");
    self->normalize = cpl_parameter_get_bool(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.profile.iterations");
    self->fit.iterations = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.profile.tests");
    self->fit.tests = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.profile.dchisquare");
    self->fit.delta = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.fit");
    self->parameter_fit = cpl_parameter_get_bool(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.yorder");
    self->yorder = cpl_parameter_get_int(p);

    if (self->yorder < 0) {
        giraffe_psf_config_destroy(self);
        self = NULL;
    }

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.worder");
    self->worder = cpl_parameter_get_int(p);

    if (self->worder < 0) {
        giraffe_psf_config_destroy(self);
        self = NULL;
    }

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.sigma");
    self->clip.level = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.iterations");
    self->clip.iterations = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.psf.parameters.fraction");
    self->clip.fraction = cpl_parameter_get_double(p);

    return self;

}
