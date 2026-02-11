giraffe_model_set_tests(GiModel *self, cxint tests)
{

    cx_assert(self != NULL);

    if (tests < 1) {
        return 1;
    }

    self->fit.setup.tests = tests;

    return 0;

}
