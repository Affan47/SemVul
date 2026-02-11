validate_mdc_config(hid_t file_id,
                    H5AC_cache_config_t * ext_config_ptr,
                    hbool_t compare_init,
                    int test_num)
{

    static char msg[256];
    H5F_t * file_ptr = NULL;
    H5C_t * cache_ptr = NULL;
    H5AC_cache_config_t scratch;
    H5C_auto_size_ctl_t int_config;

    XLATE_EXT_TO_INT_MDC_CONFIG(int_config, (*ext_config_ptr))


    if ( pass ) {

        file_ptr = (H5F_t *)H5I_object_verify(file_id, H5I_FILE);

        if ( file_ptr == NULL ) {

            pass = FALSE;
            HDsnprintf(msg, (size_t)128, "Can't get file_ptr #%d.", test_num);
            failure_mssg = msg;

        } else {

            cache_ptr = file_ptr->shared->cache;
        }
    }


    if ( pass ) {

        if ( ( cache_ptr == NULL ) ||
             ( cache_ptr->magic != H5C__H5C_T_MAGIC ) ||
             ( cache_ptr->resize_ctl.version != H5C__CURR_AUTO_SIZE_CTL_VER ) ){

            pass = FALSE;
            HDsnprintf(msg, (size_t)128,
                       "Can't access cache resize_ctl #%d.", test_num);
            failure_mssg = msg;
        }
    }


    if ( pass ) {

	if ( ! resize_configs_are_equal(&int_config, &cache_ptr->resize_ctl,
                                        compare_init) ) {

            pass = FALSE;
            HDsnprintf(msg, (size_t)128,
                       "Unexpected internal config #%d.", test_num);
            failure_mssg = msg;
        }
    }


    if ( pass ) {

        scratch.version = H5AC__CURR_CACHE_CONFIG_VERSION;

        if ( H5Fget_mdc_config(file_id, &scratch) < 0 ) {

            pass = FALSE;
            HDsnprintf(msg, (size_t)128,
                       "H5Fget_mdc_config() failed #%d.", test_num);
            failure_mssg = msg;
        }
    }

    if ( pass ) {


        if ( ! CACHE_CONFIGS_EQUAL((*ext_config_ptr), scratch, \
                                   FALSE, compare_init) ) {

            pass = FALSE;
            HDsnprintf(msg, (size_t)128,
                       "Unexpected external config #%d.", test_num);
            failure_mssg = msg;
        }
    }

    return;

}
