cpl_imagelist_collapse_minmax_create(const cpl_imagelist * self,
                                                 cpl_size              nlow,
                                                 cpl_size              nhigh)
{
    const cpl_image * imgself = cpl_imagelist_get_const(self, 0);
    const cpl_type    type    = cpl_image_get_type(imgself);
    const size_t      ni      = cpl_imagelist_get_size(self);
    const size_t      nx      = cpl_image_get_size_x(imgself);
    const size_t      ny      = cpl_image_get_size_y(imgself);
    const size_t      nrej    = (size_t)(nlow + nhigh);
    cpl_image       * avg     = NULL;


    cpl_ensure(self != NULL,  CPL_ERROR_NULL_INPUT, NULL);
    cpl_ensure(cpl_imagelist_is_uniform(self)==0, CPL_ERROR_ILLEGAL_INPUT,
               NULL);
    cpl_ensure(nlow  >= 0,    CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(nhigh >= 0,    CPL_ERROR_ILLEGAL_INPUT, NULL);
    cpl_ensure(ni    >  nrej, CPL_ERROR_ILLEGAL_INPUT, NULL);


    switch (type) {
#define CPL_CLASS CPL_CLASS_DOUBLE
#include "cpl_imagelist_basic_body.h"
#undef CPL_CLASS

#define CPL_CLASS CPL_CLASS_FLOAT
#include "cpl_imagelist_basic_body.h"
#undef CPL_CLASS

#define CPL_CLASS CPL_CLASS_INT
#include "cpl_imagelist_basic_body.h"
#undef CPL_CLASS
        default:
            (void)cpl_error_set_(CPL_ERROR_INVALID_TYPE);
    }

    return avg;
}
